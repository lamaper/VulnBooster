static int decode(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt)

{

    BC_STATUS ret;

    BC_DTS_STATUS decoder_status = { 0, };

    CopyRet rec_ret;

    CHDContext *priv   = avctx->priv_data;

    HANDLE dev         = priv->dev;

    uint8_t *in_data   = avpkt->data;

    int len            = avpkt->size;

    int free_data      = 0;

    uint8_t pic_type   = 0;



    av_log(avctx, AV_LOG_VERBOSE, "CrystalHD: decode_frame\n");



    if (avpkt->size == 7 && !priv->bframe_bug) {

         

        av_log(avctx, AV_LOG_INFO,

               "CrystalHD: Enabling work-around for packed b-frame bug\n");

        priv->bframe_bug = 1;

    } else if (avpkt->size == 8 && priv->bframe_bug) {

         

        av_log(avctx, AV_LOG_INFO,

               "CrystalHD: Disabling work-around for packed b-frame bug\n");

        priv->bframe_bug = 0;

    }



    if (len) {

        int32_t tx_free = (int32_t)DtsTxFreeSize(dev);



        if (priv->bsfc) {

            int ret = 0;

            AVPacket filter_packet = { 0 };

            AVPacket filtered_packet = { 0 };



            ret = av_packet_ref(&filter_packet, avpkt);

            if (ret < 0) {

                av_log(avctx, AV_LOG_ERROR, "CrystalHD: mpv4toannexb filter "

                       "failed to ref input packet\n");

                return ret;

            }



              ret = av_bsf_send_packet(priv->bsfc, &filter_packet);

              if (ret < 0) {

                av_log(avctx, AV_LOG_ERROR, "CrystalHD: mpv4toannexb filter "

                       "failed to send input packet\n");

                return ret;

            }



            ret = av_bsf_receive_packet(priv->bsfc, &filtered_packet);

            if (ret < 0) {

                av_log(avctx, AV_LOG_ERROR, "CrystalHD: mpv4toannexb filter "

                       "failed to receive output packet\n");

                return ret;

            }



            in_data = filtered_packet.data;

            len = filtered_packet.size;



            av_packet_unref(&filter_packet);

        }



        if (priv->parser) {

            int ret = 0;



            free_data = ret > 0;



            if (ret >= 0) {

                uint8_t *pout;

                int psize;

                int index;

                H264Context *h = priv->parser->priv_data;



                index = av_parser_parse2(priv->parser, avctx, &pout, &psize,

                                         in_data, len, avctx->internal->pkt->pts,

                                         avctx->internal->pkt->dts, 0);

                if (index < 0) {

                    av_log(avctx, AV_LOG_WARNING,

                           "CrystalHD: Failed to parse h.264 packet to "

                           "detect interlacing.\n");

                } else if (index != len) {

                    av_log(avctx, AV_LOG_WARNING,

                           "CrystalHD: Failed to parse h.264 packet "

                           "completely. Interlaced frames may be "

                           "incorrectly detected.\n");

                } else {

                    av_log(avctx, AV_LOG_VERBOSE,

                           "CrystalHD: parser picture type %d\n",

                           h->picture_structure);

                    pic_type = h->picture_structure;

                }

            } else {

                av_log(avctx, AV_LOG_WARNING,

                       "CrystalHD: mp4toannexb filter failed to filter "

                       "packet. Interlaced frames may be incorrectly "

                       "detected.\n");

            }

        }



        if (len < tx_free - 1024) {

             

            uint64_t pts = opaque_list_push(priv, avctx->internal->pkt->pts, pic_type);

            if (!pts) {

                if (free_data) {

                    av_freep(&in_data);

                }

                return AVERROR(ENOMEM);

            }

            av_log(priv->avctx, AV_LOG_VERBOSE,

                   "input \"pts\": %"PRIu64"\n", pts);

            ret = DtsProcInput(dev, in_data, len, pts, 0);

            if (free_data) {

                av_freep(&in_data);

            }

            if (ret == BC_STS_BUSY) {

                av_log(avctx, AV_LOG_WARNING,

                       "CrystalHD: ProcInput returned busy\n");

                usleep(BASE_WAIT);

                return AVERROR(EBUSY);

            } else if (ret != BC_STS_SUCCESS) {

                av_log(avctx, AV_LOG_ERROR,

                       "CrystalHD: ProcInput failed: %u\n", ret);

                return -1;

            }

            avctx->has_b_frames++;

        } else {

            av_log(avctx, AV_LOG_WARNING, "CrystalHD: Input buffer full\n");

            len = 0;  

        }

    } else {

        av_log(avctx, AV_LOG_INFO, "CrystalHD: No more input data\n");

    }



    if (priv->skip_next_output) {

        av_log(avctx, AV_LOG_VERBOSE, "CrystalHD: Skipping next output.\n");

        priv->skip_next_output = 0;

        avctx->has_b_frames--;

        return len;

    }



    ret = DtsGetDriverStatus(dev, &decoder_status);

    if (ret != BC_STS_SUCCESS) {

        av_log(avctx, AV_LOG_ERROR, "CrystalHD: GetDriverStatus failed\n");

        return -1;

    }



     

    if (priv->output_ready < 2) {

        if (decoder_status.ReadyListCount != 0)

            priv->output_ready++;

        usleep(BASE_WAIT);

        av_log(avctx, AV_LOG_INFO, "CrystalHD: Filling pipeline.\n");

        return len;

    } else if (decoder_status.ReadyListCount == 0) {

         

        usleep(BASE_WAIT);

        priv->decode_wait += WAIT_UNIT;

        av_log(avctx, AV_LOG_INFO, "CrystalHD: No frames ready. Returning\n");

        return len;

    }



    do {

        rec_ret = receive_frame(avctx, data, got_frame);

        if (rec_ret == RET_OK && *got_frame == 0) {

             

            av_log(avctx, AV_LOG_VERBOSE, "Returning after first field.\n");

            avctx->has_b_frames--;

        } else if (rec_ret == RET_COPY_NEXT_FIELD) {

             

            av_log(avctx, AV_LOG_VERBOSE, "Trying to get second field.\n");

            while (1) {

                usleep(priv->decode_wait);

                ret = DtsGetDriverStatus(dev, &decoder_status);

                if (ret == BC_STS_SUCCESS &&

                    decoder_status.ReadyListCount > 0) {

                    rec_ret = receive_frame(avctx, data, got_frame);

                    if ((rec_ret == RET_OK && *got_frame > 0) ||

                        rec_ret == RET_ERROR)

                        break;

                }

            }

            av_log(avctx, AV_LOG_VERBOSE, "CrystalHD: Got second field.\n");

        } else if (rec_ret == RET_SKIP_NEXT_COPY) {

             

            av_log(avctx, AV_LOG_VERBOSE,

                   "Don't output on next decode call.\n");

            priv->skip_next_output = 1;

        }

         

    } while (rec_ret == RET_COPY_AGAIN);

    usleep(priv->decode_wait);

    return len;

}

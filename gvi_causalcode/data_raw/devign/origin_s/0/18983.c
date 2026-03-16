int avformat_find_stream_info(AVFormatContext *ic, AVDictionary **options)

{

    int i, count, ret, read_size, j;

    AVStream *st;

    AVPacket pkt1, *pkt;

    int64_t old_offset = avio_tell(ic->pb);

    int orig_nb_streams = ic->nb_streams;         



    for(i=0;i<ic->nb_streams;i++) {

        AVCodec *codec;

        AVDictionary *thread_opt = NULL;

        st = ic->streams[i];



        if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO ||

            st->codec->codec_type == AVMEDIA_TYPE_SUBTITLE) {

 

            if(!st->codec->time_base.num)

                st->codec->time_base= st->time_base;

        }

         

        if (!st->parser && !(ic->flags & AVFMT_FLAG_NOPARSE)) {

            st->parser = av_parser_init(st->codec->codec_id);

            if(st->need_parsing == AVSTREAM_PARSE_HEADERS && st->parser){

                st->parser->flags |= PARSER_FLAG_COMPLETE_FRAMES;

            }

        }

        assert(!st->codec->codec);

        codec = avcodec_find_decoder(st->codec->codec_id);



         

        av_dict_set(options ? &options[i] : &thread_opt, "threads", "1", 0);



         

        if (st->codec->codec_type == AVMEDIA_TYPE_SUBTITLE

            && codec && !st->codec->codec)

            avcodec_open2(st->codec, codec, options ? &options[i]

                              : &thread_opt);



         

        if(!has_codec_parameters(st->codec)){

            if (codec && !st->codec->codec)

                avcodec_open2(st->codec, codec, options ? &options[i]

                              : &thread_opt);

        }

        if (!options)

            av_dict_free(&thread_opt);

    }



    for (i=0; i<ic->nb_streams; i++) {

        ic->streams[i]->info->last_dts = AV_NOPTS_VALUE;

    }



    count = 0;

    read_size = 0;

    for(;;) {

        if (ff_check_interrupt(&ic->interrupt_callback)){

            ret= AVERROR_EXIT;

            av_log(ic, AV_LOG_DEBUG, "interrupted\n");

            break;

        }



         

        for(i=0;i<ic->nb_streams;i++) {

            int fps_analyze_framecount = 20;



            st = ic->streams[i];

            if (!has_codec_parameters(st->codec))

                break;

             

            if (av_q2d(st->time_base) > 0.0005)

                fps_analyze_framecount *= 2;

            if (ic->fps_probe_size >= 0)

                fps_analyze_framecount = ic->fps_probe_size;

             

            if(   tb_unreliable(st->codec) && !(st->r_frame_rate.num && st->avg_frame_rate.num)

               && st->info->duration_count < fps_analyze_framecount

               && st->codec->codec_type == AVMEDIA_TYPE_VIDEO)

                break;

            if(st->parser && st->parser->parser->split && !st->codec->extradata)

                break;

            if(st->first_dts == AV_NOPTS_VALUE)

                break;

        }

        if (i == ic->nb_streams) {

             

            if (!(ic->ctx_flags & AVFMTCTX_NOHEADER)) {

                 

                ret = count;

                av_log(ic, AV_LOG_DEBUG, "All info found\n");

                break;

            }

        }

         

        if (read_size >= ic->probesize) {

            ret = count;

            av_log(ic, AV_LOG_DEBUG, "Probe buffer size limit %d reached\n", ic->probesize);

            break;

        }



         

        ret = read_frame_internal(ic, &pkt1);

        if (ret == AVERROR(EAGAIN))

            continue;



        if (ret < 0) {

             

            AVPacket empty_pkt = { 0 };

            int err;

            av_init_packet(&empty_pkt);



            ret = -1;  

            for(i=0;i<ic->nb_streams;i++) {

                st = ic->streams[i];



                 

                do {

                    err = try_decode_frame(st, &empty_pkt,

                                           (options && i < orig_nb_streams) ?

                                           &options[i] : NULL);

                } while (err > 0 && !has_codec_parameters(st->codec));



                if (err < 0) {

                    av_log(ic, AV_LOG_WARNING,

                           "decoding for stream %d failed\n", st->index);

                } else if (!has_codec_parameters(st->codec)){

                    char buf[256];

                    avcodec_string(buf, sizeof(buf), st->codec, 0);

                    av_log(ic, AV_LOG_WARNING,

                           "Could not find codec parameters (%s)\n", buf);

                } else {

                    ret = 0;

                }

            }

            break;

        }



        pkt= add_to_pktbuf(&ic->packet_buffer, &pkt1, &ic->packet_buffer_end);

        if ((ret = av_dup_packet(pkt)) < 0)

            goto find_stream_info_err;



        read_size += pkt->size;



        st = ic->streams[pkt->stream_index];

        if (st->codec_info_nb_frames>1) {

            if (st->time_base.den > 0 && av_rescale_q(st->info->codec_info_duration, st->time_base, AV_TIME_BASE_Q) >= ic->max_analyze_duration) {

                av_log(ic, AV_LOG_WARNING, "max_analyze_duration reached\n");

                break;

            }

            st->info->codec_info_duration += pkt->duration;

        }

        {

            int64_t last = st->info->last_dts;



            if(pkt->dts != AV_NOPTS_VALUE && last != AV_NOPTS_VALUE && pkt->dts > last){

                int64_t duration= pkt->dts - last;

                double dur= duration * av_q2d(st->time_base);



 

 

                if (st->info->duration_count < 2)

                    memset(st->info->duration_error, 0, sizeof(st->info->duration_error));

                for (i=1; i<FF_ARRAY_ELEMS(st->info->duration_error); i++) {

                    int framerate= get_std_framerate(i);

                    int ticks= lrintf(dur*framerate/(1001*12));

                    double error = dur - (double)ticks*1001*12 / framerate;

                    st->info->duration_error[i] += error*error;

                }

                st->info->duration_count++;

                 

                if (st->info->duration_count > 3)

                    st->info->duration_gcd = av_gcd(st->info->duration_gcd, duration);

            }

            if (last == AV_NOPTS_VALUE || st->info->duration_count <= 1)

                st->info->last_dts = pkt->dts;

        }

        if(st->parser && st->parser->parser->split && !st->codec->extradata){

            int i= st->parser->parser->split(st->codec, pkt->data, pkt->size);

            if (i > 0 && i < FF_MAX_EXTRADATA_SIZE) {

                st->codec->extradata_size= i;

                st->codec->extradata= av_malloc(st->codec->extradata_size + FF_INPUT_BUFFER_PADDING_SIZE);

                if (!st->codec->extradata)

                    return AVERROR(ENOMEM);

                memcpy(st->codec->extradata, pkt->data, st->codec->extradata_size);

                memset(st->codec->extradata + i, 0, FF_INPUT_BUFFER_PADDING_SIZE);

            }

        }



         

        try_decode_frame(st, pkt, (options && i < orig_nb_streams ) ? &options[i] : NULL);



        st->codec_info_nb_frames++;

        count++;

    }



     

    for(i=0;i<ic->nb_streams;i++) {

        st = ic->streams[i];

        if(st->codec->codec)

            avcodec_close(st->codec);

    }

    for(i=0;i<ic->nb_streams;i++) {

        st = ic->streams[i];

        if (st->codec_info_nb_frames>2 && !st->avg_frame_rate.num && st->info->codec_info_duration)

            av_reduce(&st->avg_frame_rate.num, &st->avg_frame_rate.den,

                     (st->codec_info_nb_frames-2)*(int64_t)st->time_base.den,

                      st->info->codec_info_duration*(int64_t)st->time_base.num, 60000);

        if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO) {

             

             

             

            if (tb_unreliable(st->codec) && st->info->duration_count > 15 && st->info->duration_gcd > 1 && !st->r_frame_rate.num)

                av_reduce(&st->r_frame_rate.num, &st->r_frame_rate.den, st->time_base.den, st->time_base.num * st->info->duration_gcd, INT_MAX);

            if (st->info->duration_count && !st->r_frame_rate.num

               && tb_unreliable(st->codec)  ){

                int num = 0;

                double best_error= 2*av_q2d(st->time_base);

                best_error = best_error*best_error*st->info->duration_count*1000*12*30;



                for (j=1; j<FF_ARRAY_ELEMS(st->info->duration_error); j++) {

                    double error = st->info->duration_error[j] * get_std_framerate(j);

 

 

                    if(error < best_error){

                        best_error= error;

                        num = get_std_framerate(j);

                    }

                }

                 

                if (num && (!st->r_frame_rate.num || (double)num/(12*1001) < 1.01 * av_q2d(st->r_frame_rate)))

                    av_reduce(&st->r_frame_rate.num, &st->r_frame_rate.den, num, 12*1001, INT_MAX);

            }



            if (!st->r_frame_rate.num){

                if(    st->codec->time_base.den * (int64_t)st->time_base.num

                    <= st->codec->time_base.num * st->codec->ticks_per_frame * (int64_t)st->time_base.den){

                    st->r_frame_rate.num = st->codec->time_base.den;

                    st->r_frame_rate.den = st->codec->time_base.num * st->codec->ticks_per_frame;

                }else{

                    st->r_frame_rate.num = st->time_base.den;

                    st->r_frame_rate.den = st->time_base.num;

                }

            }

        }else if(st->codec->codec_type == AVMEDIA_TYPE_AUDIO) {

            if(!st->codec->bits_per_coded_sample)

                st->codec->bits_per_coded_sample= av_get_bits_per_sample(st->codec->codec_id);

             

            switch (st->codec->audio_service_type) {

            case AV_AUDIO_SERVICE_TYPE_EFFECTS:

                st->disposition = AV_DISPOSITION_CLEAN_EFFECTS;    break;

            case AV_AUDIO_SERVICE_TYPE_VISUALLY_IMPAIRED:

                st->disposition = AV_DISPOSITION_VISUAL_IMPAIRED;  break;

            case AV_AUDIO_SERVICE_TYPE_HEARING_IMPAIRED:

                st->disposition = AV_DISPOSITION_HEARING_IMPAIRED; break;

            case AV_AUDIO_SERVICE_TYPE_COMMENTARY:

                st->disposition = AV_DISPOSITION_COMMENT;          break;

            case AV_AUDIO_SERVICE_TYPE_KARAOKE:

                st->disposition = AV_DISPOSITION_KARAOKE;          break;

            }

        }

    }



    estimate_timings(ic, old_offset);



    compute_chapters_end(ic);


     

    for(i=0;i<ic->nb_streams;i++) {

        st = ic->streams[i];

        if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO) {

            if(b-frames){

                ppktl = &ic->packet_buffer;

                while(ppkt1){

                    if(ppkt1->stream_index != i)

                        continue;

                    if(ppkt1->pkt->dts < 0)

                        break;

                    if(ppkt1->pkt->pts != AV_NOPTS_VALUE)

                        break;

                    ppkt1->pkt->dts -= delta;

                    ppkt1= ppkt1->next;

                }

                if(ppkt1)

                    continue;

                st->cur_dts -= delta;

            }

        }

    }




 find_stream_info_err:

    for (i=0; i < ic->nb_streams; i++) {

        if (ic->streams[i]->codec)

            ic->streams[i]->codec->thread_count = 0;

        av_freep(&ic->streams[i]->info);

    }

    return ret;

}

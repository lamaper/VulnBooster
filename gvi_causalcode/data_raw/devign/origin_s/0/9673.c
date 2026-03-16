static av_cold int cuvid_decode_init(AVCodecContext *avctx)

{

    CuvidContext *ctx = avctx->priv_data;

    AVCUDADeviceContext *device_hwctx;

    AVHWDeviceContext *device_ctx;

    AVHWFramesContext *hwframe_ctx;

    CUVIDSOURCEDATAPACKET seq_pkt;

    CUcontext cuda_ctx = NULL;

    CUcontext dummy;

    const AVBitStreamFilter *bsf;

    int ret = 0;



    enum AVPixelFormat pix_fmts[3] = { AV_PIX_FMT_CUDA,

                                       AV_PIX_FMT_NV12,

                                       AV_PIX_FMT_NONE };



    int probed_width = avctx->coded_width ? avctx->coded_width : 1280;

    int probed_height = avctx->coded_height ? avctx->coded_height : 720;



     

     

     

     

    ret = ff_get_format(avctx, pix_fmts);

    if (ret < 0) {

        av_log(avctx, AV_LOG_ERROR, "ff_get_format failed: %d\n", ret);

        return ret;

    }

    avctx->pix_fmt = ret;



    if (ctx->resize_expr && sscanf(ctx->resize_expr, "%dx%d",

                                   &ctx->resize.width, &ctx->resize.height) != 2) {

        av_log(avctx, AV_LOG_ERROR, "Invalid resize expressions\n");

        ret = AVERROR(EINVAL);

        goto error;

    }



    if (ctx->crop_expr && sscanf(ctx->crop_expr, "%dx%dx%dx%d",

                                 &ctx->crop.top, &ctx->crop.bottom,

                                 &ctx->crop.left, &ctx->crop.right) != 4) {

        av_log(avctx, AV_LOG_ERROR, "Invalid cropping expressions\n");

        ret = AVERROR(EINVAL);

        goto error;

    }



    ret = cuvid_load_functions(&ctx->cvdl);

    if (ret < 0) {

        av_log(avctx, AV_LOG_ERROR, "Failed loading nvcuvid.\n");

        goto error;

    }



    ctx->frame_queue = av_fifo_alloc(ctx->nb_surfaces * sizeof(CuvidParsedFrame));

    if (!ctx->frame_queue) {

        ret = AVERROR(ENOMEM);

        goto error;

    }



    if (avctx->hw_frames_ctx) {

        ctx->hwframe = av_buffer_ref(avctx->hw_frames_ctx);

        if (!ctx->hwframe) {

            ret = AVERROR(ENOMEM);

            goto error;

        }



        hwframe_ctx = (AVHWFramesContext*)ctx->hwframe->data;



        ctx->hwdevice = av_buffer_ref(hwframe_ctx->device_ref);

        if (!ctx->hwdevice) {

            ret = AVERROR(ENOMEM);

            goto error;

        }

    } else {

        if (avctx->hw_device_ctx) {

            ctx->hwdevice = av_buffer_ref(avctx->hw_device_ctx);

            if (!ctx->hwdevice) {

                ret = AVERROR(ENOMEM);

                goto error;

            }

        } else {

            ret = av_hwdevice_ctx_create(&ctx->hwdevice, AV_HWDEVICE_TYPE_CUDA, ctx->cu_gpu, NULL, 0);

            if (ret < 0)

                goto error;

        }



        ctx->hwframe = av_hwframe_ctx_alloc(ctx->hwdevice);

        if (!ctx->hwframe) {

            av_log(avctx, AV_LOG_ERROR, "av_hwframe_ctx_alloc failed\n");

            ret = AVERROR(ENOMEM);

            goto error;

        }



        hwframe_ctx = (AVHWFramesContext*)ctx->hwframe->data;

    }



    device_ctx = hwframe_ctx->device_ctx;

    device_hwctx = device_ctx->hwctx;



    cuda_ctx = device_hwctx->cuda_ctx;

    ctx->cudl = device_hwctx->internal->cuda_dl;



    memset(&ctx->cuparseinfo, 0, sizeof(ctx->cuparseinfo));

    memset(&ctx->cuparse_ext, 0, sizeof(ctx->cuparse_ext));

    memset(&seq_pkt, 0, sizeof(seq_pkt));



    ctx->cuparseinfo.pExtVideoInfo = &ctx->cuparse_ext;



    switch (avctx->codec->id) {


    case AV_CODEC_ID_H264:

        ctx->cuparseinfo.CodecType = cudaVideoCodec_H264;

        break;



    case AV_CODEC_ID_HEVC:

        ctx->cuparseinfo.CodecType = cudaVideoCodec_HEVC;

        break;



    case AV_CODEC_ID_MJPEG:

        ctx->cuparseinfo.CodecType = cudaVideoCodec_JPEG;

        break;



    case AV_CODEC_ID_MPEG1VIDEO:

        ctx->cuparseinfo.CodecType = cudaVideoCodec_MPEG1;

        break;



    case AV_CODEC_ID_MPEG2VIDEO:

        ctx->cuparseinfo.CodecType = cudaVideoCodec_MPEG2;

        break;



    case AV_CODEC_ID_MPEG4:

        ctx->cuparseinfo.CodecType = cudaVideoCodec_MPEG4;

        break;



    case AV_CODEC_ID_VP8:

        ctx->cuparseinfo.CodecType = cudaVideoCodec_VP8;

        break;



    case AV_CODEC_ID_VP9:

        ctx->cuparseinfo.CodecType = cudaVideoCodec_VP9;

        break;



    case AV_CODEC_ID_VC1:

        ctx->cuparseinfo.CodecType = cudaVideoCodec_VC1;

        break;


    default:

        av_log(avctx, AV_LOG_ERROR, "Invalid CUVID codec!\n");

        return AVERROR_BUG;

    }



    if (avctx->codec->id == AV_CODEC_ID_H264 || avctx->codec->id == AV_CODEC_ID_HEVC) {

        if (avctx->codec->id == AV_CODEC_ID_H264)

            bsf = av_bsf_get_by_name("h264_mp4toannexb");

        else

            bsf = av_bsf_get_by_name("hevc_mp4toannexb");



        if (!bsf) {

            ret = AVERROR_BSF_NOT_FOUND;

            goto error;

        }

        if (ret = av_bsf_alloc(bsf, &ctx->bsf)) {

            goto error;

        }

        if (((ret = avcodec_parameters_from_context(ctx->bsf->par_in, avctx)) < 0) || ((ret = av_bsf_init(ctx->bsf)) < 0)) {

            av_bsf_free(&ctx->bsf);

            goto error;

        }



        ctx->cuparse_ext.format.seqhdr_data_length = ctx->bsf->par_out->extradata_size;

        memcpy(ctx->cuparse_ext.raw_seqhdr_data,

               ctx->bsf->par_out->extradata,

               FFMIN(sizeof(ctx->cuparse_ext.raw_seqhdr_data), ctx->bsf->par_out->extradata_size));

    } else if (avctx->extradata_size > 0) {

        ctx->cuparse_ext.format.seqhdr_data_length = avctx->extradata_size;

        memcpy(ctx->cuparse_ext.raw_seqhdr_data,

               avctx->extradata,

               FFMIN(sizeof(ctx->cuparse_ext.raw_seqhdr_data), avctx->extradata_size));

    }



    ctx->cuparseinfo.ulMaxNumDecodeSurfaces = ctx->nb_surfaces;

    ctx->cuparseinfo.ulMaxDisplayDelay = 4;

    ctx->cuparseinfo.pUserData = avctx;

    ctx->cuparseinfo.pfnSequenceCallback = cuvid_handle_video_sequence;

    ctx->cuparseinfo.pfnDecodePicture = cuvid_handle_picture_decode;

    ctx->cuparseinfo.pfnDisplayPicture = cuvid_handle_picture_display;



    ret = CHECK_CU(ctx->cudl->cuCtxPushCurrent(cuda_ctx));

    if (ret < 0)

        goto error;



    ret = cuvid_test_dummy_decoder(avctx, &ctx->cuparseinfo,

                                   probed_width,

                                   probed_height);

    if (ret < 0)

        goto error;



    ret = CHECK_CU(ctx->cvdl->cuvidCreateVideoParser(&ctx->cuparser, &ctx->cuparseinfo));

    if (ret < 0)

        goto error;



    seq_pkt.payload = ctx->cuparse_ext.raw_seqhdr_data;

    seq_pkt.payload_size = ctx->cuparse_ext.format.seqhdr_data_length;



    if (seq_pkt.payload && seq_pkt.payload_size) {

        ret = CHECK_CU(ctx->cvdl->cuvidParseVideoData(ctx->cuparser, &seq_pkt));

        if (ret < 0)

            goto error;

    }



    ret = CHECK_CU(ctx->cudl->cuCtxPopCurrent(&dummy));

    if (ret < 0)

        goto error;



    ctx->prev_pts = INT64_MIN;



    if (!avctx->pkt_timebase.num || !avctx->pkt_timebase.den)

        av_log(avctx, AV_LOG_WARNING, "Invalid pkt_timebase, passing timestamps as-is.\n");



    return 0;



error:

    cuvid_decode_end(avctx);

    return ret;

}

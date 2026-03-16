int ff_thread_init(AVCodecContext *avctx)

{

    if (avctx->thread_opaque) {

        av_log(avctx, AV_LOG_ERROR, "avcodec_thread_init is ignored after avcodec_open\n");

        return -1;

    }


    w32thread_init();




    if (avctx->codec) {

        validate_thread_parameters(avctx);



        if (avctx->active_thread_type&FF_THREAD_SLICE)

            return thread_init(avctx);

        else if (avctx->active_thread_type&FF_THREAD_FRAME)

            return frame_thread_init(avctx);

    }



    return 0;

}

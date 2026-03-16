static void warn_insufficient_frame_quality ( AVCodecContext * avctx , const char * message ) {
 av_log ( avctx , AV_LOG_WARNING , "Frame #%d, IFQ: %s\n" , avctx -> frame_number , message ) ;
 }
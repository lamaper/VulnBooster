static int flic_decode_frame_24BPP ( AVCodecContext * avctx , void * data , int * got_frame , const uint8_t * buf , int buf_size ) {
 av_log ( avctx , AV_LOG_ERROR , "24Bpp FLC Unsupported due to lack of test files.\n" ) ;
 return AVERROR_PATCHWELCOME ;
 }
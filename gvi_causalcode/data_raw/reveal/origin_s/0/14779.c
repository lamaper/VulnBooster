static int codec_reinit ( AVCodecContext * avctx , int width , int height , int quality ) {
 NuvContext * c = avctx -> priv_data ;
 int ret ;
 width = FFALIGN ( width , 2 ) ;
 height = FFALIGN ( height , 2 ) ;
 if ( quality >= 0 ) get_quant_quality ( c , quality ) ;
 if ( width != c -> width || height != c -> height ) {
 if ( ( ret = av_image_check_size ( height , width , 0 , avctx ) ) < 0 ) return ret ;
 avctx -> width = c -> width = width ;
 avctx -> height = c -> height = height ;
 av_fast_malloc ( & c -> decomp_buf , & c -> decomp_size , c -> height * c -> width * 3 / 2 ) ;
 if ( ! c -> decomp_buf ) {
 av_log ( avctx , AV_LOG_ERROR , "Can't allocate decompression buffer.\n" ) ;
 return AVERROR ( ENOMEM ) ;
 }
 ff_rtjpeg_decode_init ( & c -> rtj , & c -> dsp , c -> width , c -> height , c -> lq , c -> cq ) ;
 }
 else if ( quality != c -> quality ) ff_rtjpeg_decode_init ( & c -> rtj , & c -> dsp , c -> width , c -> height , c -> lq , c -> cq ) ;
 return 0 ;
 }
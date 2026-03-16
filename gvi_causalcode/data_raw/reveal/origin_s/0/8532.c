static int set_bps_params ( AVCodecContext * avctx ) {
 switch ( avctx -> bits_per_coded_sample ) {
 case 8 : avctx -> sample_fmt = AV_SAMPLE_FMT_U8P ;
 break ;
 case 16 : avctx -> sample_fmt = AV_SAMPLE_FMT_S16P ;
 break ;
 case 24 : avctx -> sample_fmt = AV_SAMPLE_FMT_S32P ;
 break ;
 default : av_log ( avctx , AV_LOG_ERROR , "unsupported bits per sample: %d\n" , avctx -> bits_per_coded_sample ) ;
 return AVERROR_INVALIDDATA ;
 }
 avctx -> bits_per_raw_sample = avctx -> bits_per_coded_sample ;
 return 0 ;
 }
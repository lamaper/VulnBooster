static void mpeg_decode_gop ( AVCodecContext * avctx , const uint8_t * buf , int buf_size ) {
 Mpeg1Context * s1 = avctx -> priv_data ;
 MpegEncContext * s = & s1 -> mpeg_enc_ctx ;
 int time_code_hours , time_code_minutes ;
 int time_code_seconds , time_code_pictures ;
 int broken_link ;
 init_get_bits ( & s -> gb , buf , buf_size * 8 ) ;
 skip_bits1 ( & s -> gb ) ;
 time_code_hours = get_bits ( & s -> gb , 5 ) ;
 time_code_minutes = get_bits ( & s -> gb , 6 ) ;
 skip_bits1 ( & s -> gb ) ;
 time_code_seconds = get_bits ( & s -> gb , 6 ) ;
 time_code_pictures = get_bits ( & s -> gb , 6 ) ;
 s1 -> closed_gop = get_bits1 ( & s -> gb ) ;
 broken_link = get_bits1 ( & s -> gb ) ;
 if ( s -> avctx -> debug & FF_DEBUG_PICT_INFO ) av_log ( s -> avctx , AV_LOG_DEBUG , "GOP (%2d:%02d:%02d.[%02d]) closed_gop=%d broken_link=%d\n" , time_code_hours , time_code_minutes , time_code_seconds , time_code_pictures , s1 -> closed_gop , broken_link ) ;
 }
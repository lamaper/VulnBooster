static int get_quant ( AVCodecContext * avctx , NuvContext * c , const uint8_t * buf , int size ) {
 int i ;
 if ( size < 2 * 64 * 4 ) {
 av_log ( avctx , AV_LOG_ERROR , "insufficient rtjpeg quant data\n" ) ;
 return AVERROR_INVALIDDATA ;
 }
 for ( i = 0 ;
 i < 64 ;
 i ++ , buf += 4 ) c -> lq [ i ] = AV_RL32 ( buf ) ;
 for ( i = 0 ;
 i < 64 ;
 i ++ , buf += 4 ) c -> cq [ i ] = AV_RL32 ( buf ) ;
 return 0 ;
 }
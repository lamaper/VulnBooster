static int read_patterns ( AVCodecContext * avctx , GetBitContext * gb , Bundle * b ) {
 int t , v ;
 const uint8_t * dec_end ;
 CHECK_READ_VAL ( gb , b , t ) ;
 dec_end = b -> cur_dec + t ;
 if ( dec_end > b -> data_end ) {
 av_log ( avctx , AV_LOG_ERROR , "Too many pattern values\n" ) ;
 return AVERROR_INVALIDDATA ;
 }
 while ( b -> cur_dec < dec_end ) {
 v = GET_HUFF ( gb , b -> tree ) ;
 v |= GET_HUFF ( gb , b -> tree ) << 4 ;
 * b -> cur_dec ++ = v ;
 }
 return 0 ;
 }
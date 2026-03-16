static int read_runs ( AVCodecContext * avctx , GetBitContext * gb , Bundle * b ) {
 int t , v ;
 const uint8_t * dec_end ;
 CHECK_READ_VAL ( gb , b , t ) ;
 dec_end = b -> cur_dec + t ;
 if ( dec_end > b -> data_end ) {
 av_log ( avctx , AV_LOG_ERROR , "Run value went out of bounds\n" ) ;
 return AVERROR_INVALIDDATA ;
 }
 if ( get_bits1 ( gb ) ) {
 v = get_bits ( gb , 4 ) ;
 memset ( b -> cur_dec , v , t ) ;
 b -> cur_dec += t ;
 }
 else {
 while ( b -> cur_dec < dec_end ) * b -> cur_dec ++ = GET_HUFF ( gb , b -> tree ) ;
 }
 return 0 ;
 }
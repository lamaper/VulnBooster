static int read_block_types ( AVCodecContext * avctx , GetBitContext * gb , Bundle * b ) {
 int t , v ;
 int last = 0 ;
 const uint8_t * dec_end ;
 CHECK_READ_VAL ( gb , b , t ) ;
 dec_end = b -> cur_dec + t ;
 if ( dec_end > b -> data_end ) {
 av_log ( avctx , AV_LOG_ERROR , "Too many block type values\n" ) ;
 return AVERROR_INVALIDDATA ;
 }
 if ( get_bits1 ( gb ) ) {
 v = get_bits ( gb , 4 ) ;
 memset ( b -> cur_dec , v , t ) ;
 b -> cur_dec += t ;
 }
 else {
 while ( b -> cur_dec < dec_end ) {
 v = GET_HUFF ( gb , b -> tree ) ;
 if ( v < 12 ) {
 last = v ;
 * b -> cur_dec ++ = v ;
 }
 else {
 int run = bink_rlelens [ v - 12 ] ;
 if ( dec_end - b -> cur_dec < run ) return AVERROR_INVALIDDATA ;
 memset ( b -> cur_dec , last , run ) ;
 b -> cur_dec += run ;
 }
 }
 }
 return 0 ;
 }
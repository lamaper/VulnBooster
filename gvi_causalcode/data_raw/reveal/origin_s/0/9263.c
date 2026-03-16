static int read_colors ( GetBitContext * gb , Bundle * b , BinkContext * c ) {
 int t , sign , v ;
 const uint8_t * dec_end ;
 CHECK_READ_VAL ( gb , b , t ) ;
 dec_end = b -> cur_dec + t ;
 if ( dec_end > b -> data_end ) {
 av_log ( c -> avctx , AV_LOG_ERROR , "Too many color values\n" ) ;
 return AVERROR_INVALIDDATA ;
 }
 if ( get_bits1 ( gb ) ) {
 c -> col_lastval = GET_HUFF ( gb , c -> col_high [ c -> col_lastval ] ) ;
 v = GET_HUFF ( gb , b -> tree ) ;
 v = ( c -> col_lastval << 4 ) | v ;
 if ( c -> version < 'i' ) {
 sign = ( ( int8_t ) v ) >> 7 ;
 v = ( ( v & 0x7F ) ^ sign ) - sign ;
 v += 0x80 ;
 }
 memset ( b -> cur_dec , v , t ) ;
 b -> cur_dec += t ;
 }
 else {
 while ( b -> cur_dec < dec_end ) {
 c -> col_lastval = GET_HUFF ( gb , c -> col_high [ c -> col_lastval ] ) ;
 v = GET_HUFF ( gb , b -> tree ) ;
 v = ( c -> col_lastval << 4 ) | v ;
 if ( c -> version < 'i' ) {
 sign = ( ( int8_t ) v ) >> 7 ;
 v = ( ( v & 0x7F ) ^ sign ) - sign ;
 v += 0x80 ;
 }
 * b -> cur_dec ++ = v ;
 }
 }
 return 0 ;
 }
static int binkb_read_bundle ( BinkContext * c , GetBitContext * gb , int bundle_num ) {
 const int bits = binkb_bundle_sizes [ bundle_num ] ;
 const int mask = 1 << ( bits - 1 ) ;
 const int issigned = binkb_bundle_signed [ bundle_num ] ;
 Bundle * b = & c -> bundle [ bundle_num ] ;
 int i , len ;
 CHECK_READ_VAL ( gb , b , len ) ;
 if ( b -> data_end - b -> cur_dec < len * ( 1 + ( bits > 8 ) ) ) return AVERROR_INVALIDDATA ;
 if ( bits <= 8 ) {
 if ( ! issigned ) {
 for ( i = 0 ;
 i < len ;
 i ++ ) * b -> cur_dec ++ = get_bits ( gb , bits ) ;
 }
 else {
 for ( i = 0 ;
 i < len ;
 i ++ ) * b -> cur_dec ++ = get_bits ( gb , bits ) - mask ;
 }
 }
 else {
 int16_t * dst = ( int16_t * ) b -> cur_dec ;
 if ( ! issigned ) {
 for ( i = 0 ;
 i < len ;
 i ++ ) * dst ++ = get_bits ( gb , bits ) ;
 }
 else {
 for ( i = 0 ;
 i < len ;
 i ++ ) * dst ++ = get_bits ( gb , bits ) - mask ;
 }
 b -> cur_dec = ( uint8_t * ) dst ;
 }
 return 0 ;
 }
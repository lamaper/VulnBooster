static int scale_vector ( int16_t * dst , const int16_t * vector , int length ) {
 int bits , max = 0 ;
 int i ;
 for ( i = 0 ;
 i < length ;
 i ++ ) max |= FFABS ( vector [ i ] ) ;
 max = FFMIN ( max , 0x7FFF ) ;
 bits = normalize_bits ( max , 15 ) ;
 for ( i = 0 ;
 i < length ;
 i ++ ) dst [ i ] = vector [ i ] << bits >> 3 ;
 return bits - 3 ;
 }
static inline void iir_filter ( int16_t * fir_coef , int16_t * iir_coef , int16_t * src , int * dest ) {
 int m , n ;
 for ( m = 0 ;
 m < SUBFRAME_LEN ;
 m ++ ) {
 int64_t filter = 0 ;
 for ( n = 1 ;
 n <= LPC_ORDER ;
 n ++ ) {
 filter -= fir_coef [ n - 1 ] * src [ m - n ] - iir_coef [ n - 1 ] * ( dest [ m - n ] >> 16 ) ;
 }
 dest [ m ] = av_clipl_int32 ( ( src [ m ] << 16 ) + ( filter << 3 ) + ( 1 << 15 ) ) ;
 }
 }
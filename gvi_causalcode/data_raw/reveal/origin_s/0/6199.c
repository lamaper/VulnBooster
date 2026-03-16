static inline void int8x8_fmul_int32 ( float * dst , const int8_t * src , int scale ) {
 float fscale = scale / 16.0 ;
 int i ;
 for ( i = 0 ;
 i < 8 ;
 i ++ ) dst [ i ] = src [ i ] * fscale ;
 }
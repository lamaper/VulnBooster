static inline int get_context ( PlaneContext * p , int16_t * src , int16_t * last , int16_t * last2 ) {
 const int LT = last [ - 1 ] ;
 const int T = last [ 0 ] ;
 const int RT = last [ 1 ] ;
 const int L = src [ - 1 ] ;
 if ( p -> quant_table [ 3 ] [ 127 ] ) {
 const int TT = last2 [ 0 ] ;
 const int LL = src [ - 2 ] ;
 return p -> quant_table [ 0 ] [ ( L - LT ) & 0xFF ] + p -> quant_table [ 1 ] [ ( LT - T ) & 0xFF ] + p -> quant_table [ 2 ] [ ( T - RT ) & 0xFF ] + p -> quant_table [ 3 ] [ ( LL - L ) & 0xFF ] + p -> quant_table [ 4 ] [ ( TT - T ) & 0xFF ] ;
 }
 else return p -> quant_table [ 0 ] [ ( L - LT ) & 0xFF ] + p -> quant_table [ 1 ] [ ( LT - T ) & 0xFF ] + p -> quant_table [ 2 ] [ ( T - RT ) & 0xFF ] ;
 }
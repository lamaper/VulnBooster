static inline int predict ( int16_t * src , int16_t * last ) {
 const int LT = last [ - 1 ] ;
 const int T = last [ 0 ] ;
 const int L = src [ - 1 ] ;
 return mid_pred ( L , L + T - LT , T ) ;
 }
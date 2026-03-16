static void sbr_hf_gen_c ( float ( * X_high ) [ 2 ] , const float ( * X_low ) [ 2 ] , const float alpha0 [ 2 ] , const float alpha1 [ 2 ] , float bw , int start , int end ) {
 float alpha [ 4 ] ;
 int i ;
 alpha [ 0 ] = alpha1 [ 0 ] * bw * bw ;
 alpha [ 1 ] = alpha1 [ 1 ] * bw * bw ;
 alpha [ 2 ] = alpha0 [ 0 ] * bw ;
 alpha [ 3 ] = alpha0 [ 1 ] * bw ;
 for ( i = start ;
 i < end ;
 i ++ ) {
 X_high [ i ] [ 0 ] = X_low [ i - 2 ] [ 0 ] * alpha [ 0 ] - X_low [ i - 2 ] [ 1 ] * alpha [ 1 ] + X_low [ i - 1 ] [ 0 ] * alpha [ 2 ] - X_low [ i - 1 ] [ 1 ] * alpha [ 3 ] + X_low [ i ] [ 0 ] ;
 X_high [ i ] [ 1 ] = X_low [ i - 2 ] [ 1 ] * alpha [ 0 ] + X_low [ i - 2 ] [ 0 ] * alpha [ 1 ] + X_low [ i - 1 ] [ 1 ] * alpha [ 2 ] + X_low [ i - 1 ] [ 0 ] * alpha [ 3 ] + X_low [ i ] [ 1 ] ;
 }
 }
static void pitch_sharpening ( int pitch_lag_int , float beta , float * fixed_vector ) {
 int i ;
 for ( i = pitch_lag_int ;
 i < SUBFR_SIZE ;
 i ++ ) fixed_vector [ i ] += beta * fixed_vector [ i - pitch_lag_int ] ;
 }
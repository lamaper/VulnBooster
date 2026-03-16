static void pitch_sharpening ( AMRWBContext * ctx , float * fixed_vector ) {
 int i ;
 for ( i = AMRWB_SFR_SIZE - 1 ;
 i != 0 ;
 i -- ) fixed_vector [ i ] -= fixed_vector [ i - 1 ] * ctx -> tilt_coef ;
 for ( i = ctx -> pitch_lag_int ;
 i < AMRWB_SFR_SIZE ;
 i ++ ) fixed_vector [ i ] += fixed_vector [ i - ctx -> pitch_lag_int ] * 0.85 ;
 }
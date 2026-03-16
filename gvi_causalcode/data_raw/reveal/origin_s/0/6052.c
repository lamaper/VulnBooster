static void gen_dirac_train ( int16_t * buf , int pitch_lag ) {
 int16_t vector [ SUBFRAME_LEN ] ;
 int i , j ;
 memcpy ( vector , buf , SUBFRAME_LEN * sizeof ( * vector ) ) ;
 for ( i = pitch_lag ;
 i < SUBFRAME_LEN ;
 i += pitch_lag ) {
 for ( j = 0 ;
 j < SUBFRAME_LEN - i ;
 j ++ ) buf [ i + j ] += vector [ j ] ;
 }
 }
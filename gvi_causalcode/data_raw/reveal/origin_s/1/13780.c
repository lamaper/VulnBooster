static void sbr_sum64x5_c ( float * z ) {
 int k ;
 for ( k = 0 ;
 k < 64 ;
 k ++ ) {
 float f = z [ k ] + z [ k + 64 ] + z [ k + 128 ] + z [ k + 192 ] + z [ k + 256 ] ;
 z [ k ] = f ;
 }
 }
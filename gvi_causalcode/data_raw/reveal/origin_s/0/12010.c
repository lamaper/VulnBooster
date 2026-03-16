void vp8_transform_intra_mby ( MACROBLOCK * x ) {
 int i ;
 for ( i = 0 ;
 i < 16 ;
 i += 2 ) {
 x -> short_fdct8x4 ( & x -> block [ i ] . src_diff [ 0 ] , & x -> block [ i ] . coeff [ 0 ] , 32 ) ;
 }
 build_dcblock ( x ) ;
 x -> short_walsh4x4 ( & x -> block [ 24 ] . src_diff [ 0 ] , & x -> block [ 24 ] . coeff [ 0 ] , 8 ) ;
 }
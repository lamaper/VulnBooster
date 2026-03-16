static void transform_mb ( MACROBLOCK * x ) {
 int i ;
 for ( i = 0 ;
 i < 16 ;
 i += 2 ) {
 x -> short_fdct8x4 ( & x -> block [ i ] . src_diff [ 0 ] , & x -> block [ i ] . coeff [ 0 ] , 32 ) ;
 }
 if ( x -> e_mbd . mode_info_context -> mbmi . mode != SPLITMV ) build_dcblock ( x ) ;
 for ( i = 16 ;
 i < 24 ;
 i += 2 ) {
 x -> short_fdct8x4 ( & x -> block [ i ] . src_diff [ 0 ] , & x -> block [ i ] . coeff [ 0 ] , 16 ) ;
 }
 if ( x -> e_mbd . mode_info_context -> mbmi . mode != SPLITMV ) x -> short_walsh4x4 ( & x -> block [ 24 ] . src_diff [ 0 ] , & x -> block [ 24 ] . coeff [ 0 ] , 8 ) ;
 }
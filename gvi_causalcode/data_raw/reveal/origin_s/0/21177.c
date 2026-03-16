void vp8_quantize_mby_c ( MACROBLOCK * x ) {
 int i ;
 int has_2nd_order = ( x -> e_mbd . mode_info_context -> mbmi . mode != B_PRED && x -> e_mbd . mode_info_context -> mbmi . mode != SPLITMV ) ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) x -> quantize_b ( & x -> block [ i ] , & x -> e_mbd . block [ i ] ) ;
 if ( has_2nd_order ) x -> quantize_b ( & x -> block [ 24 ] , & x -> e_mbd . block [ 24 ] ) ;
 }
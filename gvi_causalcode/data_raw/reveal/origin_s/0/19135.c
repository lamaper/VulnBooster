void vp8_quantize_mb_c ( MACROBLOCK * x ) {
 int i ;
 int has_2nd_order = ( x -> e_mbd . mode_info_context -> mbmi . mode != B_PRED && x -> e_mbd . mode_info_context -> mbmi . mode != SPLITMV ) ;
 for ( i = 0 ;
 i < 24 + has_2nd_order ;
 i ++ ) x -> quantize_b ( & x -> block [ i ] , & x -> e_mbd . block [ i ] ) ;
 }
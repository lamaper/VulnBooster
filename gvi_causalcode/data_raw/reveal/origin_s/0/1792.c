void vp8_quantize_mbuv_c ( MACROBLOCK * x ) {
 int i ;
 for ( i = 16 ;
 i < 24 ;
 i ++ ) x -> quantize_b ( & x -> block [ i ] , & x -> e_mbd . block [ i ] ) ;
 }
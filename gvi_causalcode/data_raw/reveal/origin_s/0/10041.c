void vp8_transform_mbuv ( MACROBLOCK * x ) {
 int i ;
 for ( i = 16 ;
 i < 24 ;
 i += 2 ) {
 x -> short_fdct8x4 ( & x -> block [ i ] . src_diff [ 0 ] , & x -> block [ i ] . coeff [ 0 ] , 16 ) ;
 }
 }
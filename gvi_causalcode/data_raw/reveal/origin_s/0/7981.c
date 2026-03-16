void vp8_fast_quantize_b_pair_c ( BLOCK * b1 , BLOCK * b2 , BLOCKD * d1 , BLOCKD * d2 ) {
 vp8_fast_quantize_b_c ( b1 , d1 ) ;
 vp8_fast_quantize_b_c ( b2 , d2 ) ;
 }
void vp8_regular_quantize_b_pair ( BLOCK * b1 , BLOCK * b2 , BLOCKD * d1 , BLOCKD * d2 ) {
 vp8_regular_quantize_b ( b1 , d1 ) ;
 vp8_regular_quantize_b ( b2 , d2 ) ;
 }
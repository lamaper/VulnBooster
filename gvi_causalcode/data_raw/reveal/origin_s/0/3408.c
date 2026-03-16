void vp8_fast_quantize_b_c ( BLOCK * b , BLOCKD * d ) {
 int i , rc , eob ;
 int x , y , z , sz ;
 short * coeff_ptr = b -> coeff ;
 short * round_ptr = b -> round ;
 short * quant_ptr = b -> quant_fast ;
 short * qcoeff_ptr = d -> qcoeff ;
 short * dqcoeff_ptr = d -> dqcoeff ;
 short * dequant_ptr = d -> dequant ;
 eob = - 1 ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) {
 rc = vp8_default_zig_zag1d [ i ] ;
 z = coeff_ptr [ rc ] ;
 sz = ( z >> 31 ) ;
 x = ( z ^ sz ) - sz ;
 y = ( ( x + round_ptr [ rc ] ) * quant_ptr [ rc ] ) >> 16 ;
 x = ( y ^ sz ) - sz ;
 qcoeff_ptr [ rc ] = x ;
 dqcoeff_ptr [ rc ] = x * dequant_ptr [ rc ] ;
 if ( y ) {
 eob = i ;
 }
 }
 * d -> eob = ( char ) ( eob + 1 ) ;
 }
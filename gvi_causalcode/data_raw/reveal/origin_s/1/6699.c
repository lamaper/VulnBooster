void vp8_strict_quantize_b_c ( BLOCK * b , BLOCKD * d ) {
 int i ;
 int rc ;
 int eob ;
 int x ;
 int y ;
 int z ;
 int sz ;
 short * coeff_ptr ;
 short * quant_ptr ;
 short * quant_shift_ptr ;
 short * qcoeff_ptr ;
 short * dqcoeff_ptr ;
 short * dequant_ptr ;
 coeff_ptr = b -> coeff ;
 quant_ptr = b -> quant ;
 quant_shift_ptr = b -> quant_shift ;
 qcoeff_ptr = d -> qcoeff ;
 dqcoeff_ptr = d -> dqcoeff ;
 dequant_ptr = d -> dequant ;
 eob = - 1 ;
 vpx_memset ( qcoeff_ptr , 0 , 32 ) ;
 vpx_memset ( dqcoeff_ptr , 0 , 32 ) ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) {
 int dq ;
 int rounding ;
 rc = vp8_default_zig_zag1d [ i ] ;
 z = coeff_ptr [ rc ] ;
 dq = dequant_ptr [ rc ] ;
 rounding = dq >> 1 ;
 sz = - ( z < 0 ) ;
 x = ( z + sz ) ^ sz ;
 x += rounding ;
 if ( x >= dq ) {
 y = ( ( ( ( x * quant_ptr [ rc ] ) >> 16 ) + x ) * quant_shift_ptr [ rc ] ) >> 16 ;
 x = ( y + sz ) ^ sz ;
 qcoeff_ptr [ rc ] = x ;
 dqcoeff_ptr [ rc ] = x * dq ;
 if ( y ) eob = i ;
 }
 }
 * d -> eob = ( char ) ( eob + 1 ) ;
 }
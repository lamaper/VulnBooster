void vp8_regular_quantize_b_c ( BLOCK * b , BLOCKD * d ) {
 int i , rc , eob ;
 int zbin ;
 int x , y , z , sz ;
 short * zbin_boost_ptr = b -> zrun_zbin_boost ;
 short * coeff_ptr = b -> coeff ;
 short * zbin_ptr = b -> zbin ;
 short * round_ptr = b -> round ;
 short * quant_ptr = b -> quant ;
 short * quant_shift_ptr = b -> quant_shift ;
 short * qcoeff_ptr = d -> qcoeff ;
 short * dqcoeff_ptr = d -> dqcoeff ;
 short * dequant_ptr = d -> dequant ;
 short zbin_oq_value = b -> zbin_extra ;
 vpx_memset ( qcoeff_ptr , 0 , 32 ) ;
 vpx_memset ( dqcoeff_ptr , 0 , 32 ) ;
 eob = - 1 ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) {
 rc = vp8_default_zig_zag1d [ i ] ;
 z = coeff_ptr [ rc ] ;
 zbin = zbin_ptr [ rc ] + * zbin_boost_ptr + zbin_oq_value ;
 zbin_boost_ptr ++ ;
 sz = ( z >> 31 ) ;
 x = ( z ^ sz ) - sz ;
 if ( x >= zbin ) {
 x += round_ptr [ rc ] ;
 y = ( ( ( ( x * quant_ptr [ rc ] ) >> 16 ) + x ) * quant_shift_ptr [ rc ] ) >> 16 ;
 x = ( y ^ sz ) - sz ;
 qcoeff_ptr [ rc ] = x ;
 dqcoeff_ptr [ rc ] = x * dequant_ptr [ rc ] ;
 if ( y ) {
 eob = i ;
 zbin_boost_ptr = b -> zrun_zbin_boost ;
 }
 }
 }
 * d -> eob = ( char ) ( eob + 1 ) ;
 }
void vp9_quantize_b_32x32_c ( const int16_t * coeff_ptr , intptr_t n_coeffs , int skip_block , const int16_t * zbin_ptr , const int16_t * round_ptr , const int16_t * quant_ptr , const int16_t * quant_shift_ptr , int16_t * qcoeff_ptr , int16_t * dqcoeff_ptr , const int16_t * dequant_ptr , int zbin_oq_value , uint16_t * eob_ptr , const int16_t * scan , const int16_t * iscan ) {
 const int zbins [ 2 ] = {
 ROUND_POWER_OF_TWO ( zbin_ptr [ 0 ] + zbin_oq_value , 1 ) , ROUND_POWER_OF_TWO ( zbin_ptr [ 1 ] + zbin_oq_value , 1 ) }
 ;
 const int nzbins [ 2 ] = {
 zbins [ 0 ] * - 1 , zbins [ 1 ] * - 1 }
 ;
 int idx = 0 ;
 int idx_arr [ 1024 ] ;
 int i , eob = - 1 ;
 ( void ) iscan ;
 vpx_memset ( qcoeff_ptr , 0 , n_coeffs * sizeof ( int16_t ) ) ;
 vpx_memset ( dqcoeff_ptr , 0 , n_coeffs * sizeof ( int16_t ) ) ;
 if ( ! skip_block ) {
 for ( i = 0 ;
 i < n_coeffs ;
 i ++ ) {
 const int rc = scan [ i ] ;
 const int coeff = coeff_ptr [ rc ] ;
 if ( coeff >= zbins [ rc != 0 ] || coeff <= nzbins [ rc != 0 ] ) idx_arr [ idx ++ ] = i ;
 }
 for ( i = 0 ;
 i < idx ;
 i ++ ) {
 const int rc = scan [ idx_arr [ i ] ] ;
 const int coeff = coeff_ptr [ rc ] ;
 const int coeff_sign = ( coeff >> 31 ) ;
 int tmp ;
 int abs_coeff = ( coeff ^ coeff_sign ) - coeff_sign ;
 abs_coeff += ROUND_POWER_OF_TWO ( round_ptr [ rc != 0 ] , 1 ) ;
 abs_coeff = clamp ( abs_coeff , INT16_MIN , INT16_MAX ) ;
 tmp = ( ( ( ( abs_coeff * quant_ptr [ rc != 0 ] ) >> 16 ) + abs_coeff ) * quant_shift_ptr [ rc != 0 ] ) >> 15 ;
 qcoeff_ptr [ rc ] = ( tmp ^ coeff_sign ) - coeff_sign ;
 dqcoeff_ptr [ rc ] = qcoeff_ptr [ rc ] * dequant_ptr [ rc != 0 ] / 2 ;
 if ( tmp ) eob = idx_arr [ i ] ;
 }
 }
 * eob_ptr = eob + 1 ;
 }
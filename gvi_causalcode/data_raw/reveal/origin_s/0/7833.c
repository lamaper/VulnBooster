void vp9_quantize_b_c ( const tran_low_t * coeff_ptr , intptr_t n_coeffs , int skip_block , const int16_t * zbin_ptr , const int16_t * round_ptr , const int16_t * quant_ptr , const int16_t * quant_shift_ptr , tran_low_t * qcoeff_ptr , tran_low_t * dqcoeff_ptr , const int16_t * dequant_ptr , int zbin_oq_value , uint16_t * eob_ptr , const int16_t * scan , const int16_t * iscan ) {
 int i , non_zero_count = ( int ) n_coeffs , eob = - 1 ;
 const int zbins [ 2 ] = {
 zbin_ptr [ 0 ] + zbin_oq_value , zbin_ptr [ 1 ] + zbin_oq_value }
 ;
 const int nzbins [ 2 ] = {
 zbins [ 0 ] * - 1 , zbins [ 1 ] * - 1 }
 ;
 ( void ) iscan ;
 vpx_memset ( qcoeff_ptr , 0 , n_coeffs * sizeof ( * qcoeff_ptr ) ) ;
 vpx_memset ( dqcoeff_ptr , 0 , n_coeffs * sizeof ( * dqcoeff_ptr ) ) ;
 if ( ! skip_block ) {
 for ( i = ( int ) n_coeffs - 1 ;
 i >= 0 ;
 i -- ) {
 const int rc = scan [ i ] ;
 const int coeff = coeff_ptr [ rc ] ;
 if ( coeff < zbins [ rc != 0 ] && coeff > nzbins [ rc != 0 ] ) non_zero_count -- ;
 else break ;
 }
 for ( i = 0 ;
 i < non_zero_count ;
 i ++ ) {
 const int rc = scan [ i ] ;
 const int coeff = coeff_ptr [ rc ] ;
 const int coeff_sign = ( coeff >> 31 ) ;
 const int abs_coeff = ( coeff ^ coeff_sign ) - coeff_sign ;
 if ( abs_coeff >= zbins [ rc != 0 ] ) {
 int tmp = clamp ( abs_coeff + round_ptr [ rc != 0 ] , INT16_MIN , INT16_MAX ) ;
 tmp = ( ( ( ( tmp * quant_ptr [ rc != 0 ] ) >> 16 ) + tmp ) * quant_shift_ptr [ rc != 0 ] ) >> 16 ;
 qcoeff_ptr [ rc ] = ( tmp ^ coeff_sign ) - coeff_sign ;
 dqcoeff_ptr [ rc ] = qcoeff_ptr [ rc ] * dequant_ptr [ rc != 0 ] ;
 if ( tmp ) eob = i ;
 }
 }
 }
 * eob_ptr = eob + 1 ;
 }
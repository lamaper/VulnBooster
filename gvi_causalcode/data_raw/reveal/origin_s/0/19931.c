void vp9_quantize_fp_c ( const tran_low_t * coeff_ptr , intptr_t n_coeffs , int skip_block , const int16_t * zbin_ptr , const int16_t * round_ptr , const int16_t * quant_ptr , const int16_t * quant_shift_ptr , tran_low_t * qcoeff_ptr , tran_low_t * dqcoeff_ptr , const int16_t * dequant_ptr , int zbin_oq_value , uint16_t * eob_ptr , const int16_t * scan , const int16_t * iscan ) {
 int i , eob = - 1 ;
 ( void ) zbin_ptr ;
 ( void ) quant_shift_ptr ;
 ( void ) zbin_oq_value ;
 ( void ) iscan ;
 vpx_memset ( qcoeff_ptr , 0 , n_coeffs * sizeof ( * qcoeff_ptr ) ) ;
 vpx_memset ( dqcoeff_ptr , 0 , n_coeffs * sizeof ( * dqcoeff_ptr ) ) ;
 if ( ! skip_block ) {
 for ( i = 0 ;
 i < n_coeffs ;
 i ++ ) {
 const int rc = scan [ i ] ;
 const int coeff = coeff_ptr [ rc ] ;
 const int coeff_sign = ( coeff >> 31 ) ;
 const int abs_coeff = ( coeff ^ coeff_sign ) - coeff_sign ;
 int tmp = clamp ( abs_coeff + round_ptr [ rc != 0 ] , INT16_MIN , INT16_MAX ) ;
 tmp = ( tmp * quant_ptr [ rc != 0 ] ) >> 16 ;
 qcoeff_ptr [ rc ] = ( tmp ^ coeff_sign ) - coeff_sign ;
 dqcoeff_ptr [ rc ] = qcoeff_ptr [ rc ] * dequant_ptr [ rc != 0 ] ;
 if ( tmp ) eob = i ;
 }
 }
 * eob_ptr = eob + 1 ;
 }
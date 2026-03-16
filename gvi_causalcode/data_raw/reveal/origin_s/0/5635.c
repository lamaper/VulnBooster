void vp9_quantize_dc_32x32 ( const tran_low_t * coeff_ptr , int skip_block , const int16_t * round_ptr , const int16_t quant , tran_low_t * qcoeff_ptr , tran_low_t * dqcoeff_ptr , const int16_t dequant_ptr , uint16_t * eob_ptr ) {
 const int rc = 0 ;
 const int coeff = coeff_ptr [ rc ] ;
 const int coeff_sign = ( coeff >> 31 ) ;
 const int abs_coeff = ( coeff ^ coeff_sign ) - coeff_sign ;
 int tmp , eob = - 1 ;
 if ( ! skip_block ) {
 tmp = clamp ( abs_coeff + round_ptr [ rc != 0 ] , INT16_MIN , INT16_MAX ) ;
 tmp = ( tmp * quant ) >> 15 ;
 qcoeff_ptr [ rc ] = ( tmp ^ coeff_sign ) - coeff_sign ;
 dqcoeff_ptr [ rc ] = qcoeff_ptr [ rc ] * dequant_ptr / 2 ;
 if ( tmp ) eob = 0 ;
 }
 * eob_ptr = eob + 1 ;
 }
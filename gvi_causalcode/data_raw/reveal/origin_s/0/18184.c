int ff_dct_quantize_c ( MpegEncContext * s , int16_t * block , int n , int qscale , int * overflow ) {
 int i , j , level , last_non_zero , q , start_i ;
 const int * qmat ;
 const uint8_t * scantable = s -> intra_scantable . scantable ;
 int bias ;
 int max = 0 ;
 unsigned int threshold1 , threshold2 ;
 s -> dsp . fdct ( block ) ;
 if ( s -> dct_error_sum ) s -> denoise_dct ( s , block ) ;
 if ( s -> mb_intra ) {
 if ( ! s -> h263_aic ) {
 if ( n < 4 ) q = s -> y_dc_scale ;
 else q = s -> c_dc_scale ;
 q = q << 3 ;
 }
 else q = 1 << 3 ;
 block [ 0 ] = ( block [ 0 ] + ( q >> 1 ) ) / q ;
 start_i = 1 ;
 last_non_zero = 0 ;
 qmat = s -> q_intra_matrix [ qscale ] ;
 bias = s -> intra_quant_bias << ( QMAT_SHIFT - QUANT_BIAS_SHIFT ) ;
 }
 else {
 start_i = 0 ;
 last_non_zero = - 1 ;
 qmat = s -> q_inter_matrix [ qscale ] ;
 bias = s -> inter_quant_bias << ( QMAT_SHIFT - QUANT_BIAS_SHIFT ) ;
 }
 threshold1 = ( 1 << QMAT_SHIFT ) - bias - 1 ;
 threshold2 = ( threshold1 << 1 ) ;
 for ( i = 63 ;
 i >= start_i ;
 i -- ) {
 j = scantable [ i ] ;
 level = block [ j ] * qmat [ j ] ;
 if ( ( ( unsigned ) ( level + threshold1 ) ) > threshold2 ) {
 last_non_zero = i ;
 break ;
 }
 else {
 block [ j ] = 0 ;
 }
 }
 for ( i = start_i ;
 i <= last_non_zero ;
 i ++ ) {
 j = scantable [ i ] ;
 level = block [ j ] * qmat [ j ] ;
 if ( ( ( unsigned ) ( level + threshold1 ) ) > threshold2 ) {
 if ( level > 0 ) {
 level = ( bias + level ) >> QMAT_SHIFT ;
 block [ j ] = level ;
 }
 else {
 level = ( bias - level ) >> QMAT_SHIFT ;
 block [ j ] = - level ;
 }
 max |= level ;
 }
 else {
 block [ j ] = 0 ;
 }
 }
 * overflow = s -> max_qcoeff < max ;
 if ( s -> dsp . idct_permutation_type != FF_NO_IDCT_PERM ) ff_block_permute ( block , s -> dsp . idct_permutation , scantable , last_non_zero ) ;
 return last_non_zero ;
 }
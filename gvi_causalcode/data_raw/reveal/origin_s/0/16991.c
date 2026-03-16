static void comp_ppf_coeff ( G723_1_Context * p , int offset , int pitch_lag , PPFParam * ppf , enum Rate cur_rate ) {
 int16_t scale ;
 int i ;
 int temp1 , temp2 ;
 int energy [ 5 ] = {
 0 , 0 , 0 , 0 , 0 }
 ;
 int16_t * buf = p -> audio + LPC_ORDER + offset ;
 int fwd_lag = autocorr_max ( buf , offset , & energy [ 1 ] , pitch_lag , SUBFRAME_LEN , 1 ) ;
 int back_lag = autocorr_max ( buf , offset , & energy [ 3 ] , pitch_lag , SUBFRAME_LEN , - 1 ) ;
 ppf -> index = 0 ;
 ppf -> opt_gain = 0 ;
 ppf -> sc_gain = 0x7fff ;
 if ( ! back_lag && ! fwd_lag ) return ;
 energy [ 0 ] = dot_product ( buf , buf , SUBFRAME_LEN ) ;
 if ( fwd_lag ) energy [ 2 ] = dot_product ( buf + fwd_lag , buf + fwd_lag , SUBFRAME_LEN ) ;
 if ( back_lag ) energy [ 4 ] = dot_product ( buf - back_lag , buf - back_lag , SUBFRAME_LEN ) ;
 temp1 = 0 ;
 for ( i = 0 ;
 i < 5 ;
 i ++ ) temp1 = FFMAX ( energy [ i ] , temp1 ) ;
 scale = normalize_bits ( temp1 , 31 ) ;
 for ( i = 0 ;
 i < 5 ;
 i ++ ) energy [ i ] = ( energy [ i ] << scale ) >> 16 ;
 if ( fwd_lag && ! back_lag ) {
 comp_ppf_gains ( fwd_lag , ppf , cur_rate , energy [ 0 ] , energy [ 1 ] , energy [ 2 ] ) ;
 }
 else if ( ! fwd_lag ) {
 comp_ppf_gains ( - back_lag , ppf , cur_rate , energy [ 0 ] , energy [ 3 ] , energy [ 4 ] ) ;
 }
 else {
 temp1 = energy [ 4 ] * ( ( energy [ 1 ] * energy [ 1 ] + ( 1 << 14 ) ) >> 15 ) ;
 temp2 = energy [ 2 ] * ( ( energy [ 3 ] * energy [ 3 ] + ( 1 << 14 ) ) >> 15 ) ;
 if ( temp1 >= temp2 ) {
 comp_ppf_gains ( fwd_lag , ppf , cur_rate , energy [ 0 ] , energy [ 1 ] , energy [ 2 ] ) ;
 }
 else {
 comp_ppf_gains ( - back_lag , ppf , cur_rate , energy [ 0 ] , energy [ 3 ] , energy [ 4 ] ) ;
 }
 }
 }
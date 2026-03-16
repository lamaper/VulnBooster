static void dca_exss_skip_mix_coeffs ( GetBitContext * gb , int channels , int out_ch ) {
 int i ;
 for ( i = 0 ;
 i < channels ;
 i ++ ) {
 int mix_map_mask = get_bits ( gb , out_ch ) ;
 int num_coeffs = av_popcount ( mix_map_mask ) ;
 skip_bits_long ( gb , num_coeffs * 6 ) ;
 }
 }
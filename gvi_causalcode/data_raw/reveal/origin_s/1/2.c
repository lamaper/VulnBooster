static void sbr_chirp ( SpectralBandReplication * sbr , SBRData * ch_data ) {
 int i ;
 float new_bw ;
 static const float bw_tab [ ] = {
 0.0f , 0.75f , 0.9f , 0.98f }
 ;
 for ( i = 0 ;
 i < sbr -> n_q ;
 i ++ ) {
 if ( ch_data -> bs_invf_mode [ 0 ] [ i ] + ch_data -> bs_invf_mode [ 1 ] [ i ] == 1 ) {
 new_bw = 0.6f ;
 }
 else new_bw = bw_tab [ ch_data -> bs_invf_mode [ 0 ] [ i ] ] ;
 if ( new_bw < ch_data -> bw_array [ i ] ) {
 new_bw = 0.75f * new_bw + 0.25f * ch_data -> bw_array [ i ] ;
 }
 else new_bw = 0.90625f * new_bw + 0.09375f * ch_data -> bw_array [ i ] ;
 ch_data -> bw_array [ i ] = new_bw < 0.015625f ? 0.0f : new_bw ;
 }
 }
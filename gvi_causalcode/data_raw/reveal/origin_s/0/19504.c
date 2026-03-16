static int dca_filter_channels ( DCAContext * s , int block_index ) {
 float ( * subband_samples ) [ DCA_SUBBANDS ] [ 8 ] = s -> subband_samples [ block_index ] ;
 int k ;
 for ( k = 0 ;
 k < s -> prim_channels ;
 k ++ ) {
 if ( s -> channel_order_tab [ k ] >= 0 ) qmf_32_subbands ( s , k , subband_samples [ k ] , s -> samples_chanptr [ s -> channel_order_tab [ k ] ] , M_SQRT1_2 / 32768.0 ) ;
 }
 if ( s -> avctx -> request_channels == 2 && s -> prim_channels > 2 ) {
 dca_downmix ( s -> samples_chanptr , s -> amode , s -> downmix_coef , s -> channel_order_tab ) ;
 }
 if ( s -> output & DCA_LFE ) {
 lfe_interpolation_fir ( s , s -> lfe , 2 * s -> lfe , s -> lfe_data + 2 * s -> lfe * ( block_index + 4 ) , s -> samples_chanptr [ dca_lfe_index [ s -> amode ] ] , 1.0 / ( 256.0 * 32768.0 ) ) ;
 }
 return 0 ;
 }
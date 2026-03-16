static void dca_exss_parse_header ( DCAContext * s ) {
 int ss_index ;
 int blownup ;
 int num_audiop = 1 ;
 int num_assets = 1 ;
 int active_ss_mask [ 8 ] ;
 int i , j ;
 if ( get_bits_left ( & s -> gb ) < 52 ) return ;
 skip_bits ( & s -> gb , 8 ) ;
 ss_index = get_bits ( & s -> gb , 2 ) ;
 blownup = get_bits1 ( & s -> gb ) ;
 skip_bits ( & s -> gb , 8 + 4 * blownup ) ;
 skip_bits ( & s -> gb , 16 + 4 * blownup ) ;
 s -> static_fields = get_bits1 ( & s -> gb ) ;
 if ( s -> static_fields ) {
 skip_bits ( & s -> gb , 2 ) ;
 skip_bits ( & s -> gb , 3 ) ;
 if ( get_bits1 ( & s -> gb ) ) skip_bits_long ( & s -> gb , 36 ) ;
 num_audiop = get_bits ( & s -> gb , 3 ) + 1 ;
 if ( num_audiop > 1 ) {
 av_log_ask_for_sample ( s -> avctx , "Multiple DTS-HD audio presentations." ) ;
 return ;
 }
 num_assets = get_bits ( & s -> gb , 3 ) + 1 ;
 if ( num_assets > 1 ) {
 av_log_ask_for_sample ( s -> avctx , "Multiple DTS-HD audio assets." ) ;
 return ;
 }
 for ( i = 0 ;
 i < num_audiop ;
 i ++ ) active_ss_mask [ i ] = get_bits ( & s -> gb , ss_index + 1 ) ;
 for ( i = 0 ;
 i < num_audiop ;
 i ++ ) for ( j = 0 ;
 j <= ss_index ;
 j ++ ) if ( active_ss_mask [ i ] & ( 1 << j ) ) skip_bits ( & s -> gb , 8 ) ;
 s -> mix_metadata = get_bits1 ( & s -> gb ) ;
 if ( s -> mix_metadata ) {
 int mix_out_mask_size ;
 skip_bits ( & s -> gb , 2 ) ;
 mix_out_mask_size = ( get_bits ( & s -> gb , 2 ) + 1 ) << 2 ;
 s -> num_mix_configs = get_bits ( & s -> gb , 2 ) + 1 ;
 for ( i = 0 ;
 i < s -> num_mix_configs ;
 i ++ ) {
 int mix_out_mask = get_bits ( & s -> gb , mix_out_mask_size ) ;
 s -> mix_config_num_ch [ i ] = dca_exss_mask2count ( mix_out_mask ) ;
 }
 }
 }
 for ( i = 0 ;
 i < num_assets ;
 i ++ ) skip_bits_long ( & s -> gb , 16 + 4 * blownup ) ;
 for ( i = 0 ;
 i < num_assets ;
 i ++ ) {
 if ( dca_exss_parse_asset_header ( s ) ) return ;
 }
 }
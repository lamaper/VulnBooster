void assign_layer_bitrates ( const SvcContext * svc_ctx , vpx_codec_enc_cfg_t * const enc_cfg ) {
 int i ;
 const SvcInternal * const si = get_const_svc_internal ( svc_ctx ) ;
 if ( si -> bitrates [ 0 ] != 0 ) {
 enc_cfg -> rc_target_bitrate = 0 ;
 for ( i = 0 ;
 i < svc_ctx -> spatial_layers ;
 ++ i ) {
 enc_cfg -> ss_target_bitrate [ i ] = ( unsigned int ) si -> bitrates [ i ] ;
 enc_cfg -> rc_target_bitrate += si -> bitrates [ i ] ;
 }
 }
 else {
 float total = 0 ;
 float alloc_ratio [ VPX_SS_MAX_LAYERS ] = {
 0 }
 ;
 for ( i = 0 ;
 i < svc_ctx -> spatial_layers ;
 ++ i ) {
 if ( si -> svc_params . scaling_factor_den [ i ] > 0 ) {
 alloc_ratio [ i ] = ( float ) ( si -> svc_params . scaling_factor_num [ i ] * 1.0 / si -> svc_params . scaling_factor_den [ i ] ) ;
 alloc_ratio [ i ] *= alloc_ratio [ i ] ;
 total += alloc_ratio [ i ] ;
 }
 }
 for ( i = 0 ;
 i < svc_ctx -> spatial_layers ;
 ++ i ) {
 if ( total > 0 ) {
 enc_cfg -> ss_target_bitrate [ i ] = ( unsigned int ) ( enc_cfg -> rc_target_bitrate * alloc_ratio [ i ] / total ) ;
 }
 }
 }
 }
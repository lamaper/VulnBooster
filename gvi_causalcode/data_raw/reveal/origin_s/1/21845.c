static vpx_codec_err_t ctrl_set_svc_parameters ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 VP9_COMP * const cpi = ctx -> cpi ;
 vpx_svc_parameters_t * const params = va_arg ( args , vpx_svc_parameters_t * ) ;
 if ( params == NULL || params -> spatial_layer < 0 || params -> spatial_layer >= cpi -> svc . number_spatial_layers ) return VPX_CODEC_INVALID_PARAM ;
 if ( params -> spatial_layer == 0 ) {
 int i ;
 for ( i = 0 ;
 i < cpi -> svc . number_spatial_layers ;
 ++ i ) {
 cpi -> svc . layer_context [ i ] . svc_params_received . spatial_layer = - 1 ;
 }
 }
 cpi -> svc . layer_context [ params -> spatial_layer ] . svc_params_received = * params ;
 return VPX_CODEC_OK ;
 }
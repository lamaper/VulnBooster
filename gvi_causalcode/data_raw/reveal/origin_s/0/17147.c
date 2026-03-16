static vpx_codec_err_t ctrl_set_svc_layer_id ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 vpx_svc_layer_id_t * const data = va_arg ( args , vpx_svc_layer_id_t * ) ;
 VP9_COMP * const cpi = ( VP9_COMP * ) ctx -> cpi ;
 SVC * const svc = & cpi -> svc ;
 svc -> spatial_layer_id = data -> spatial_layer_id ;
 svc -> temporal_layer_id = data -> temporal_layer_id ;
 if ( svc -> temporal_layer_id < 0 || svc -> temporal_layer_id >= ( int ) ctx -> cfg . ts_number_layers ) {
 return VPX_CODEC_INVALID_PARAM ;
 }
 if ( svc -> spatial_layer_id < 0 || svc -> spatial_layer_id >= ( int ) ctx -> cfg . ss_number_layers ) {
 return VPX_CODEC_INVALID_PARAM ;
 }
 return VPX_CODEC_OK ;
 }
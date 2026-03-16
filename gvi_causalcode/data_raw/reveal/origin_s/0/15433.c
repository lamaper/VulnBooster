static vpx_codec_err_t ctrl_set_svc_parameters ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 VP9_COMP * const cpi = ctx -> cpi ;
 vpx_svc_extra_cfg_t * const params = va_arg ( args , vpx_svc_extra_cfg_t * ) ;
 int i ;
 for ( i = 0 ;
 i < cpi -> svc . number_spatial_layers ;
 ++ i ) {
 LAYER_CONTEXT * lc = & cpi -> svc . layer_context [ i ] ;
 lc -> max_q = params -> max_quantizers [ i ] ;
 lc -> min_q = params -> min_quantizers [ i ] ;
 lc -> scaling_factor_num = params -> scaling_factor_num [ i ] ;
 lc -> scaling_factor_den = params -> scaling_factor_den [ i ] ;
 }
 return VPX_CODEC_OK ;
 }
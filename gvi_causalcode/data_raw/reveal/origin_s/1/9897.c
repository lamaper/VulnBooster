static void set_svc_parameters ( SvcContext * svc_ctx , vpx_codec_ctx_t * codec_ctx ) {
 int layer , layer_index ;
 vpx_svc_parameters_t svc_params ;
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 memset ( & svc_params , 0 , sizeof ( svc_params ) ) ;
 svc_params . temporal_layer = 0 ;
 svc_params . spatial_layer = si -> layer ;
 layer = si -> layer ;
 if ( VPX_CODEC_OK != vpx_svc_get_layer_resolution ( svc_ctx , layer , & svc_params . width , & svc_params . height ) ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "vpx_svc_get_layer_resolution failed\n" ) ;
 }
 layer_index = layer + VPX_SS_MAX_LAYERS - si -> layers ;
 if ( codec_ctx -> config . enc -> g_pass == VPX_RC_ONE_PASS ) {
 svc_params . min_quantizer = si -> quantizer [ layer_index ] ;
 svc_params . max_quantizer = si -> quantizer [ layer_index ] ;
 }
 else {
 svc_params . min_quantizer = codec_ctx -> config . enc -> rc_min_quantizer ;
 svc_params . max_quantizer = codec_ctx -> config . enc -> rc_max_quantizer ;
 }
 svc_params . distance_from_i_frame = si -> frame_within_gop ;
 vpx_codec_control ( codec_ctx , VP9E_SET_SVC_PARAMETERS , & svc_params ) ;
 }
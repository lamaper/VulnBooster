vpx_codec_err_t vpx_svc_init ( SvcContext * svc_ctx , vpx_codec_ctx_t * codec_ctx , vpx_codec_iface_t * iface , vpx_codec_enc_cfg_t * enc_cfg ) {
 vpx_codec_err_t res ;
 int i ;
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || codec_ctx == NULL || iface == NULL || enc_cfg == NULL ) {
 return VPX_CODEC_INVALID_PARAM ;
 }
 if ( si == NULL ) return VPX_CODEC_MEM_ERROR ;
 si -> codec_ctx = codec_ctx ;
 si -> width = enc_cfg -> g_w ;
 si -> height = enc_cfg -> g_h ;
 if ( enc_cfg -> kf_max_dist < 2 ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "key frame distance too small: %d\n" , enc_cfg -> kf_max_dist ) ;
 return VPX_CODEC_INVALID_PARAM ;
 }
 si -> kf_dist = enc_cfg -> kf_max_dist ;
 if ( svc_ctx -> spatial_layers == 0 ) svc_ctx -> spatial_layers = VPX_SS_DEFAULT_LAYERS ;
 if ( svc_ctx -> spatial_layers < 1 || svc_ctx -> spatial_layers > VPX_SS_MAX_LAYERS ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "spatial layers: invalid value: %d\n" , svc_ctx -> spatial_layers ) ;
 return VPX_CODEC_INVALID_PARAM ;
 }
 for ( i = 0 ;
 i < VPX_SS_MAX_LAYERS ;
 ++ i ) {
 si -> svc_params . max_quantizers [ i ] = MAX_QUANTIZER ;
 si -> svc_params . min_quantizers [ i ] = 0 ;
 si -> svc_params . scaling_factor_num [ i ] = DEFAULT_SCALE_FACTORS_NUM [ i ] ;
 si -> svc_params . scaling_factor_den [ i ] = DEFAULT_SCALE_FACTORS_DEN [ i ] ;
 }
 res = parse_options ( svc_ctx , si -> options ) ;
 if ( res != VPX_CODEC_OK ) return res ;
 if ( svc_ctx -> spatial_layers < 1 ) svc_ctx -> spatial_layers = 1 ;
 if ( svc_ctx -> spatial_layers > VPX_SS_MAX_LAYERS ) svc_ctx -> spatial_layers = VPX_SS_MAX_LAYERS ;
 if ( svc_ctx -> temporal_layers < 1 ) svc_ctx -> temporal_layers = 1 ;
 if ( svc_ctx -> temporal_layers > VPX_TS_MAX_LAYERS ) svc_ctx -> temporal_layers = VPX_TS_MAX_LAYERS ;
 assign_layer_bitrates ( svc_ctx , enc_cfg ) ;

 i < svc_ctx -> spatial_layers ;
 ++ i ) enc_cfg -> ss_enable_auto_alt_ref [ i ] = si -> enable_auto_alt_ref [ i ] ;

 int i ;
 for ( i = 0 ;
 i < svc_ctx -> temporal_layers ;
 ++ i ) {
 enc_cfg -> ts_target_bitrate [ i ] = enc_cfg -> rc_target_bitrate / svc_ctx -> temporal_layers ;
 enc_cfg -> ts_rate_decimator [ i ] = 1 << ( svc_ctx -> temporal_layers - 1 - i ) ;
 }
 }
 enc_cfg -> ss_number_layers = svc_ctx -> spatial_layers ;
 enc_cfg -> ts_number_layers = svc_ctx -> temporal_layers ;
 if ( enc_cfg -> g_error_resilient == 0 && si -> use_multiple_frame_contexts == 0 ) enc_cfg -> g_error_resilient = 1 ;
 res = vpx_codec_enc_init ( codec_ctx , iface , enc_cfg , VPX_CODEC_USE_PSNR ) ;
 if ( res != VPX_CODEC_OK ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "svc_enc_init error\n" ) ;
 return res ;
 }
 vpx_codec_control ( codec_ctx , VP9E_SET_SVC , 1 ) ;
 vpx_codec_control ( codec_ctx , VP9E_SET_SVC_PARAMETERS , & si -> svc_params ) ;
 return VPX_CODEC_OK ;
 }
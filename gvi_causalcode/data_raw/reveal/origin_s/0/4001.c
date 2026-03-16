static vpx_codec_err_t encoder_set_config ( vpx_codec_alg_priv_t * ctx , const vpx_codec_enc_cfg_t * cfg ) {
 vpx_codec_err_t res ;
 if ( cfg -> g_w != ctx -> cfg . g_w || cfg -> g_h != ctx -> cfg . g_h ) ERROR ( "Cannot change width or height after initialization" ) ;
 if ( cfg -> g_lag_in_frames > ctx -> cfg . g_lag_in_frames ) ERROR ( "Cannot increase lag_in_frames" ) ;
 res = validate_config ( ctx , cfg , & ctx -> extra_cfg ) ;
 if ( res == VPX_CODEC_OK ) {
 ctx -> cfg = * cfg ;
 set_encoder_config ( & ctx -> oxcf , & ctx -> cfg , & ctx -> extra_cfg ) ;
 vp9_change_config ( ctx -> cpi , & ctx -> oxcf ) ;
 }
 return res ;
 }
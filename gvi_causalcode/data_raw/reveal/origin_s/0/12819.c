static vpx_codec_err_t update_extra_cfg ( vpx_codec_alg_priv_t * ctx , const struct vp9_extracfg * extra_cfg ) {
 const vpx_codec_err_t res = validate_config ( ctx , & ctx -> cfg , extra_cfg ) ;
 if ( res == VPX_CODEC_OK ) {
 ctx -> extra_cfg = * extra_cfg ;
 set_encoder_config ( & ctx -> oxcf , & ctx -> cfg , & ctx -> extra_cfg ) ;
 vp9_change_config ( ctx -> cpi , & ctx -> oxcf ) ;
 }
 return res ;
 }
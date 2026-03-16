static vpx_codec_err_t ctrl_set_arnr_strength ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 struct vp9_extracfg extra_cfg = ctx -> extra_cfg ;
 extra_cfg . arnr_strength = CAST ( VP8E_SET_ARNR_STRENGTH , args ) ;
 return update_extra_cfg ( ctx , & extra_cfg ) ;
 }
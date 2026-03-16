static vpx_codec_err_t ctrl_set_tuning ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 struct vp9_extracfg extra_cfg = ctx -> extra_cfg ;
 extra_cfg . tuning = CAST ( VP8E_SET_TUNING , args ) ;
 return update_extra_cfg ( ctx , & extra_cfg ) ;
 }
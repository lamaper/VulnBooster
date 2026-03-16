static vpx_codec_err_t ctrl_set_sharpness ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 struct vp9_extracfg extra_cfg = ctx -> extra_cfg ;
 extra_cfg . sharpness = CAST ( VP8E_SET_SHARPNESS , args ) ;
 return update_extra_cfg ( ctx , & extra_cfg ) ;
 }
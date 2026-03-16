static vpx_codec_err_t ctrl_set_tune_content ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 struct vp9_extracfg extra_cfg = ctx -> extra_cfg ;
 extra_cfg . content = CAST ( VP9E_SET_TUNE_CONTENT , args ) ;
 return update_extra_cfg ( ctx , & extra_cfg ) ;
 }
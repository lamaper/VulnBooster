static vpx_codec_err_t ctrl_set_aq_mode ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 struct vp9_extracfg extra_cfg = ctx -> extra_cfg ;
 extra_cfg . aq_mode = CAST ( VP9E_SET_AQ_MODE , args ) ;
 return update_extra_cfg ( ctx , & extra_cfg ) ;
 }
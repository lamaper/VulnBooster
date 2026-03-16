static vpx_codec_err_t ctrl_set_arnr_max_frames ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 struct vp9_extracfg extra_cfg = ctx -> extra_cfg ;
 extra_cfg . arnr_max_frames = CAST ( VP8E_SET_ARNR_MAXFRAMES , args ) ;
 return update_extra_cfg ( ctx , & extra_cfg ) ;
 }
static vpx_codec_err_t ctrl_set_frame_periodic_boost ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 struct vp9_extracfg extra_cfg = ctx -> extra_cfg ;
 extra_cfg . frame_periodic_boost = CAST ( VP9E_SET_FRAME_PERIODIC_BOOST , args ) ;
 return update_extra_cfg ( ctx , & extra_cfg ) ;
 }
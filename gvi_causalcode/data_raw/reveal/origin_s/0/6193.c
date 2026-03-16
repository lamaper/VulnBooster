static vpx_codec_err_t ctrl_set_cq_level ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 struct vp9_extracfg extra_cfg = ctx -> extra_cfg ;
 extra_cfg . cq_level = CAST ( VP8E_SET_CQ_LEVEL , args ) ;
 return update_extra_cfg ( ctx , & extra_cfg ) ;
 }
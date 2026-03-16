static vpx_codec_err_t ctrl_set_rc_max_intra_bitrate_pct ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 struct vp9_extracfg extra_cfg = ctx -> extra_cfg ;
 extra_cfg . rc_max_intra_bitrate_pct = CAST ( VP8E_SET_MAX_INTRA_BITRATE_PCT , args ) ;
 return update_extra_cfg ( ctx , & extra_cfg ) ;
 }
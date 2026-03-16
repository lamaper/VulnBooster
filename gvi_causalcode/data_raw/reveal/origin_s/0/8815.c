static vpx_codec_err_t ctrl_set_tile_columns ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 struct vp9_extracfg extra_cfg = ctx -> extra_cfg ;
 extra_cfg . tile_columns = CAST ( VP9E_SET_TILE_COLUMNS , args ) ;
 return update_extra_cfg ( ctx , & extra_cfg ) ;
 }
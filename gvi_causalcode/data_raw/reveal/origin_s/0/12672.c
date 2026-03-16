static vpx_codec_err_t ctrl_set_previewpp ( vpx_codec_alg_priv_t * ctx , va_list args ) {

 if ( config != NULL ) {
 ctx -> preview_ppcfg = * config ;
 return VPX_CODEC_OK ;
 }
 else {
 return VPX_CODEC_INVALID_PARAM ;
 }

 ( void ) args ;
 return VPX_CODEC_INCAPABLE ;

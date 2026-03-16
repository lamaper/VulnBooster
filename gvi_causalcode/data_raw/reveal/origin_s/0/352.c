static vpx_codec_err_t ctrl_get_quantizer ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 int * const arg = va_arg ( args , int * ) ;
 if ( arg == NULL ) return VPX_CODEC_INVALID_PARAM ;
 * arg = vp9_get_quantizer ( ctx -> cpi ) ;
 return VPX_CODEC_OK ;
 }
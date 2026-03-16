static vpx_codec_err_t ctrl_update_entropy ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 const int update = va_arg ( args , int ) ;
 vp9_update_entropy ( ctx -> cpi , update ) ;
 return VPX_CODEC_OK ;
 }
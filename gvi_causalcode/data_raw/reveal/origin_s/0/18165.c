static vpx_codec_err_t ctrl_use_reference ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 const int reference_flag = va_arg ( args , int ) ;
 vp9_use_as_reference ( ctx -> cpi , reference_flag ) ;
 return VPX_CODEC_OK ;
 }
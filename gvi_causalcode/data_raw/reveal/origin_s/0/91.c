static vpx_codec_err_t ctrl_update_reference ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 const int ref_frame_flags = va_arg ( args , int ) ;
 vp9_update_reference ( ctx -> cpi , ref_frame_flags ) ;
 return VPX_CODEC_OK ;
 }
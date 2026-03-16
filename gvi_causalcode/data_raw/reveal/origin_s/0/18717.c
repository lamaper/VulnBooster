static vpx_codec_err_t ctrl_set_scale_mode ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 vpx_scaling_mode_t * const mode = va_arg ( args , vpx_scaling_mode_t * ) ;
 if ( mode ) {
 const int res = vp9_set_internal_size ( ctx -> cpi , ( VPX_SCALING ) mode -> h_scaling_mode , ( VPX_SCALING ) mode -> v_scaling_mode ) ;
 return ( res == 0 ) ? VPX_CODEC_OK : VPX_CODEC_INVALID_PARAM ;
 }
 else {
 return VPX_CODEC_INVALID_PARAM ;
 }
 }
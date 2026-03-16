static vpx_codec_err_t ctrl_set_active_map ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 vpx_active_map_t * const map = va_arg ( args , vpx_active_map_t * ) ;
 if ( map ) {
 if ( ! vp9_set_active_map ( ctx -> cpi , map -> active_map , ( int ) map -> rows , ( int ) map -> cols ) ) return VPX_CODEC_OK ;
 else return VPX_CODEC_INVALID_PARAM ;
 }
 else {
 return VPX_CODEC_INVALID_PARAM ;
 }
 }
static vpx_codec_err_t ctrl_get_reference ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 vp9_ref_frame_t * const frame = va_arg ( args , vp9_ref_frame_t * ) ;
 if ( frame != NULL ) {
 YV12_BUFFER_CONFIG * fb = get_ref_frame ( & ctx -> cpi -> common , frame -> idx ) ;
 if ( fb == NULL ) return VPX_CODEC_ERROR ;
 yuvconfig2image ( & frame -> img , fb , NULL ) ;
 return VPX_CODEC_OK ;
 }
 else {
 return VPX_CODEC_INVALID_PARAM ;
 }
 }
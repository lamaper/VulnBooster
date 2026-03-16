static vpx_codec_err_t ctrl_copy_reference ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 vpx_ref_frame_t * const frame = va_arg ( args , vpx_ref_frame_t * ) ;
 if ( frame != NULL ) {
 YV12_BUFFER_CONFIG sd ;
 image2yuvconfig ( & frame -> img , & sd ) ;
 vp9_copy_reference_enc ( ctx -> cpi , ref_frame_to_vp9_reframe ( frame -> frame_type ) , & sd ) ;
 return VPX_CODEC_OK ;
 }
 else {
 return VPX_CODEC_INVALID_PARAM ;
 }
 }
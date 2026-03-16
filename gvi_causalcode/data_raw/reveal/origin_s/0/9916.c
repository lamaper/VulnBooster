vpx_codec_err_t vp9_copy_reference_dec ( VP9Decoder * pbi , VP9_REFFRAME ref_frame_flag , YV12_BUFFER_CONFIG * sd ) {
 VP9_COMMON * cm = & pbi -> common ;
 if ( ref_frame_flag == VP9_LAST_FLAG ) {
 const YV12_BUFFER_CONFIG * const cfg = get_ref_frame ( cm , 0 ) ;
 if ( cfg == NULL ) {
 vpx_internal_error ( & cm -> error , VPX_CODEC_ERROR , "No 'last' reference frame" ) ;
 return VPX_CODEC_ERROR ;
 }
 if ( ! equal_dimensions ( cfg , sd ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_ERROR , "Incorrect buffer dimensions" ) ;
 else vp8_yv12_copy_frame ( cfg , sd ) ;
 }
 else {
 vpx_internal_error ( & cm -> error , VPX_CODEC_ERROR , "Invalid reference frame" ) ;
 }
 return cm -> error . error_code ;
 }
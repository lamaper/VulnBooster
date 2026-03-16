vpx_codec_err_t vp9_set_reference_dec ( VP9_COMMON * cm , VP9_REFFRAME ref_frame_flag , YV12_BUFFER_CONFIG * sd ) {
 RefBuffer * ref_buf = NULL ;
 if ( ref_frame_flag == VP9_LAST_FLAG ) {
 ref_buf = & cm -> frame_refs [ 0 ] ;
 }
 else if ( ref_frame_flag == VP9_GOLD_FLAG ) {
 ref_buf = & cm -> frame_refs [ 1 ] ;
 }
 else if ( ref_frame_flag == VP9_ALT_FLAG ) {
 ref_buf = & cm -> frame_refs [ 2 ] ;
 }
 else {
 vpx_internal_error ( & cm -> error , VPX_CODEC_ERROR , "Invalid reference frame" ) ;
 return cm -> error . error_code ;
 }
 if ( ! equal_dimensions ( ref_buf -> buf , sd ) ) {
 vpx_internal_error ( & cm -> error , VPX_CODEC_ERROR , "Incorrect buffer dimensions" ) ;
 }
 else {
 int * ref_fb_ptr = & ref_buf -> idx ;
 const int free_fb = get_free_fb ( cm ) ;
 cm -> frame_bufs [ free_fb ] . ref_count -- ;
 ref_cnt_fb ( cm -> frame_bufs , ref_fb_ptr , free_fb ) ;
 ref_buf -> buf = & cm -> frame_bufs [ * ref_fb_ptr ] . buf ;
 vp8_yv12_copy_frame ( sd , ref_buf -> buf ) ;
 }
 return cm -> error . error_code ;
 }
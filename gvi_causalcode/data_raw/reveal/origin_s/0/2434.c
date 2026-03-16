void vp9_scale_references ( VP9_COMP * cpi ) {
 VP9_COMMON * cm = & cpi -> common ;
 MV_REFERENCE_FRAME ref_frame ;
 const VP9_REFFRAME ref_mask [ 3 ] = {
 VP9_LAST_FLAG , VP9_GOLD_FLAG , VP9_ALT_FLAG }
 ;
 for ( ref_frame = LAST_FRAME ;
 ref_frame <= ALTREF_FRAME ;
 ++ ref_frame ) {
 const int idx = cm -> ref_frame_map [ get_ref_frame_idx ( cpi , ref_frame ) ] ;
 const YV12_BUFFER_CONFIG * const ref = & cm -> frame_bufs [ idx ] . buf ;
 if ( ( cpi -> ref_frame_flags & ref_mask [ ref_frame - 1 ] ) && ( ref -> y_crop_width != cm -> width || ref -> y_crop_height != cm -> height ) ) {
 const int new_fb = get_free_fb ( cm ) ;
 vp9_realloc_frame_buffer ( & cm -> frame_bufs [ new_fb ] . buf , cm -> width , cm -> height , cm -> subsampling_x , cm -> subsampling_y , # if CONFIG_VP9_HIGHBITDEPTH cm -> use_highbitdepth , # endif VP9_ENC_BORDER_IN_PIXELS , NULL , NULL , NULL ) ;
 scale_and_extend_frame ( ref , & cm -> frame_bufs [ new_fb ] . buf ) ;
 cpi -> scaled_ref_idx [ ref_frame - 1 ] = new_fb ;
 }
 else {
 cpi -> scaled_ref_idx [ ref_frame - 1 ] = idx ;
 cm -> frame_bufs [ idx ] . ref_count ++ ;
 }
 }
 }
void vp9_temporal_filter ( VP9_COMP * cpi , int distance ) {
 VP9_COMMON * const cm = & cpi -> common ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 int frame ;
 int frames_to_blur ;
 int start_frame ;
 int strength ;
 int frames_to_blur_backward ;
 int frames_to_blur_forward ;
 struct scale_factors sf ;
 YV12_BUFFER_CONFIG * frames [ MAX_LAG_BUFFERS ] = {
 NULL }
 ;
 adjust_arnr_filter ( cpi , distance , rc -> gfu_boost , & frames_to_blur , & strength ) ;
 frames_to_blur_backward = ( frames_to_blur / 2 ) ;
 frames_to_blur_forward = ( ( frames_to_blur - 1 ) / 2 ) ;
 start_frame = distance + frames_to_blur_forward ;
 for ( frame = 0 ;
 frame < frames_to_blur ;
 ++ frame ) {
 const int which_buffer = start_frame - frame ;
 struct lookahead_entry * buf = vp9_lookahead_peek ( cpi -> lookahead , which_buffer ) ;
 frames [ frames_to_blur - 1 - frame ] = & buf -> img ;
 }
 if ( is_two_pass_svc ( cpi ) ) {
 int frame_used = 0 ;
 vp9_setup_scale_factors_for_frame ( & sf , get_frame_new_buffer ( cm ) -> y_crop_width , get_frame_new_buffer ( cm ) -> y_crop_height , get_frame_new_buffer ( cm ) -> y_crop_width , get_frame_new_buffer ( cm ) -> y_crop_height ) ;
 for ( frame = 0 ;
 frame < frames_to_blur ;
 ++ frame ) {
 if ( cm -> mi_cols * MI_SIZE != frames [ frame ] -> y_width || cm -> mi_rows * MI_SIZE != frames [ frame ] -> y_height ) {
 if ( vp9_realloc_frame_buffer ( & cpi -> svc . scaled_frames [ frame_used ] , cm -> width , cm -> height , cm -> subsampling_x , cm -> subsampling_y , # if CONFIG_VP9_HIGHBITDEPTH cm -> use_highbitdepth , # endif VP9_ENC_BORDER_IN_PIXELS , NULL , NULL , NULL ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_MEM_ERROR , "Failed to reallocate alt_ref_buffer" ) ;
 frames [ frame ] = vp9_scale_if_required ( cm , frames [ frame ] , & cpi -> svc . scaled_frames [ frame_used ] ) ;
 ++ frame_used ;
 }
 }
 }
 else {
 vp9_setup_scale_factors_for_frame ( & sf , get_frame_new_buffer ( cm ) -> y_crop_width , get_frame_new_buffer ( cm ) -> y_crop_height , cm -> width , cm -> height ) ;
 }
 temporal_filter_iterate_c ( cpi , frames , frames_to_blur , frames_to_blur_backward , strength , & sf ) ;
 }
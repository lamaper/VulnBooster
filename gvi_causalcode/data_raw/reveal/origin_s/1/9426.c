static void apply_frame_size ( VP9_COMMON * cm , int width , int height ) {
 if ( cm -> width != width || cm -> height != height ) {
 if ( width > cm -> width || height > cm -> height ) {
 if ( vp9_resize_frame_buffers ( cm , width , height ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_MEM_ERROR , "Failed to allocate frame buffers" ) ;
 }
 cm -> width = width ;
 cm -> height = height ;
 vp9_update_frame_size ( cm ) ;
 }
 if ( vp9_realloc_frame_buffer ( get_frame_new_buffer ( cm ) , cm -> width , cm -> height , cm -> subsampling_x , cm -> subsampling_y , VP9_DEC_BORDER_IN_PIXELS , & cm -> frame_bufs [ cm -> new_fb_idx ] . raw_frame_buffer , cm -> get_fb_cb , cm -> cb_priv ) ) {
 vpx_internal_error ( & cm -> error , VPX_CODEC_MEM_ERROR , "Failed to allocate frame buffer" ) ;
 }
 }
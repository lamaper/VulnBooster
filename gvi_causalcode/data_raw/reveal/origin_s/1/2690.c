static void setup_frame_size_with_refs ( VP9_COMMON * cm , struct vp9_read_bit_buffer * rb ) {
 int width , height ;
 int found = 0 , i ;
 int has_valid_ref_frame = 0 ;
 for ( i = 0 ;
 i < REFS_PER_FRAME ;
 ++ i ) {
 if ( vp9_rb_read_bit ( rb ) ) {
 YV12_BUFFER_CONFIG * const buf = cm -> frame_refs [ i ] . buf ;
 width = buf -> y_crop_width ;
 height = buf -> y_crop_height ;
 if ( buf -> corrupted ) {
 vpx_internal_error ( & cm -> error , VPX_CODEC_CORRUPT_FRAME , "Frame reference is corrupt" ) ;
 }
 found = 1 ;
 break ;
 }
 }
 if ( ! found ) vp9_read_frame_size ( rb , & width , & height ) ;
 if ( width <= 0 || height <= 0 ) vpx_internal_error ( & cm -> error , VPX_CODEC_CORRUPT_FRAME , "Invalid frame size" ) ;
 for ( i = 0 ;
 i < REFS_PER_FRAME ;
 ++ i ) {
 RefBuffer * const ref_frame = & cm -> frame_refs [ i ] ;
 has_valid_ref_frame |= valid_ref_frame_size ( ref_frame -> buf -> y_crop_width , ref_frame -> buf -> y_crop_height , width , height ) ;
 }
 if ( ! has_valid_ref_frame ) vpx_internal_error ( & cm -> error , VPX_CODEC_CORRUPT_FRAME , "Referenced frame has invalid size" ) ;
 resize_context_buffers ( cm , width , height ) ;
 setup_display_size ( cm , rb ) ;
 if ( vp9_realloc_frame_buffer ( get_frame_new_buffer ( cm ) , cm -> width , cm -> height , cm -> subsampling_x , cm -> subsampling_y , # if CONFIG_VP9_HIGHBITDEPTH cm -> use_highbitdepth , # endif VP9_DEC_BORDER_IN_PIXELS , & cm -> frame_bufs [ cm -> new_fb_idx ] . raw_frame_buffer , cm -> get_fb_cb , cm -> cb_priv ) ) {
 vpx_internal_error ( & cm -> error , VPX_CODEC_MEM_ERROR , "Failed to allocate frame buffer" ) ;
 }
 }
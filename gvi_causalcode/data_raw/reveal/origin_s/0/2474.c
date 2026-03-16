static void setup_frame_size_with_refs ( VP9_COMMON * cm , struct vp9_read_bit_buffer * rb ) {
 int width , height ;
 int found = 0 , i ;
 for ( i = 0 ;
 i < REFS_PER_FRAME ;
 ++ i ) {
 if ( vp9_rb_read_bit ( rb ) ) {
 YV12_BUFFER_CONFIG * const buf = cm -> frame_refs [ i ] . buf ;
 width = buf -> y_crop_width ;
 height = buf -> y_crop_height ;
 found = 1 ;
 break ;
 }
 }
 if ( ! found ) vp9_read_frame_size ( rb , & width , & height ) ;
 for ( i = 0 ;
 i < REFS_PER_FRAME ;
 ++ i ) {
 RefBuffer * const ref_frame = & cm -> frame_refs [ i ] ;
 const int ref_width = ref_frame -> buf -> y_width ;
 const int ref_height = ref_frame -> buf -> y_height ;
 if ( ! valid_ref_frame_size ( ref_width , ref_height , width , height ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_CORRUPT_FRAME , "Referenced frame has invalid size" ) ;
 }
 apply_frame_size ( cm , width , height ) ;
 setup_display_size ( cm , rb ) ;
 }
static void setup_frame_size ( VP9_COMMON * cm , struct vp9_read_bit_buffer * rb ) {
 int width , height ;
 vp9_read_frame_size ( rb , & width , & height ) ;
 apply_frame_size ( cm , width , height ) ;
 setup_display_size ( cm , rb ) ;
 }
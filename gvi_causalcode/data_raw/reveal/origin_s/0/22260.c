static void setup_display_size ( VP9_COMMON * cm , struct vp9_read_bit_buffer * rb ) {
 cm -> display_width = cm -> width ;
 cm -> display_height = cm -> height ;
 if ( vp9_rb_read_bit ( rb ) ) vp9_read_frame_size ( rb , & cm -> display_width , & cm -> display_height ) ;
 }
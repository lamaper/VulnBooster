static void write_frame_size ( const VP9_COMMON * cm , struct vp9_write_bit_buffer * wb ) {
 vp9_wb_write_literal ( wb , cm -> width - 1 , 16 ) ;
 vp9_wb_write_literal ( wb , cm -> height - 1 , 16 ) ;
 write_display_size ( cm , wb ) ;
 }
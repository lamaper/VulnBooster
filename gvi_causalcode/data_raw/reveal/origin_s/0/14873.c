static void write_display_size ( const VP9_COMMON * cm , struct vp9_write_bit_buffer * wb ) {
 const int scaling_active = cm -> width != cm -> display_width || cm -> height != cm -> display_height ;
 vp9_wb_write_bit ( wb , scaling_active ) ;
 if ( scaling_active ) {
 vp9_wb_write_literal ( wb , cm -> display_width - 1 , 16 ) ;
 vp9_wb_write_literal ( wb , cm -> display_height - 1 , 16 ) ;
 }
 }
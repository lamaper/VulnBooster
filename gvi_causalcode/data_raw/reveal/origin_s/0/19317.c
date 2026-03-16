static void write_interp_filter ( INTERP_FILTER filter , struct vp9_write_bit_buffer * wb ) {
 const int filter_to_literal [ ] = {
 1 , 0 , 2 , 3 }
 ;
 vp9_wb_write_bit ( wb , filter == SWITCHABLE ) ;
 if ( filter != SWITCHABLE ) vp9_wb_write_literal ( wb , filter_to_literal [ filter ] , 2 ) ;
 }
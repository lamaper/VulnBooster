static void write_delta_q ( struct vp9_write_bit_buffer * wb , int delta_q ) {
 if ( delta_q != 0 ) {
 vp9_wb_write_bit ( wb , 1 ) ;
 vp9_wb_write_literal ( wb , abs ( delta_q ) , 4 ) ;
 vp9_wb_write_bit ( wb , delta_q < 0 ) ;
 }
 else {
 vp9_wb_write_bit ( wb , 0 ) ;
 }
 }
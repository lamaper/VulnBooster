static void write_sync_code ( struct vp9_write_bit_buffer * wb ) {
 vp9_wb_write_literal ( wb , VP9_SYNC_CODE_0 , 8 ) ;
 vp9_wb_write_literal ( wb , VP9_SYNC_CODE_1 , 8 ) ;
 vp9_wb_write_literal ( wb , VP9_SYNC_CODE_2 , 8 ) ;
 }
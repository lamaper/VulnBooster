int vp9_read_sync_code ( struct vp9_read_bit_buffer * const rb ) {
 return vp9_rb_read_literal ( rb , 8 ) == VP9_SYNC_CODE_0 && vp9_rb_read_literal ( rb , 8 ) == VP9_SYNC_CODE_1 && vp9_rb_read_literal ( rb , 8 ) == VP9_SYNC_CODE_2 ;
 }
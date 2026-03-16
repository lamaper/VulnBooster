static int read_delta_q ( struct vp9_read_bit_buffer * rb , int * delta_q ) {
 const int old = * delta_q ;
 * delta_q = vp9_rb_read_bit ( rb ) ? vp9_rb_read_signed_literal ( rb , 4 ) : 0 ;
 return old != * delta_q ;
 }
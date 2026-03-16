void vp9_read_frame_size ( struct vp9_read_bit_buffer * rb , int * width , int * height ) {
 const int w = vp9_rb_read_literal ( rb , 16 ) + 1 ;
 const int h = vp9_rb_read_literal ( rb , 16 ) + 1 ;
 * width = w ;
 * height = h ;
 }
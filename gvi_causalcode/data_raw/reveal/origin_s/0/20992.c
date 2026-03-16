static int decode_unsigned_max ( struct vp9_read_bit_buffer * rb , int max ) {
 const int data = vp9_rb_read_literal ( rb , get_unsigned_bits ( max ) ) ;
 return data > max ? max : data ;
 }
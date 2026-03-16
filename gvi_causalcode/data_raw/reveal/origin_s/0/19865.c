static void encode_unsigned_max ( struct vp9_write_bit_buffer * wb , int data , int max ) {
 vp9_wb_write_literal ( wb , data , get_unsigned_bits ( max ) ) ;
 }
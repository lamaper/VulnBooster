static BITSTREAM_PROFILE read_profile ( struct vp9_read_bit_buffer * rb ) {
 int profile = vp9_rb_read_bit ( rb ) ;
 profile |= vp9_rb_read_bit ( rb ) << 1 ;
 return ( BITSTREAM_PROFILE ) profile ;
 }
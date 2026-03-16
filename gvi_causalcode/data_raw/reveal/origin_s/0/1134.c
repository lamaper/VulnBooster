BITSTREAM_PROFILE vp9_read_profile ( struct vp9_read_bit_buffer * rb ) {
 int profile = vp9_rb_read_bit ( rb ) ;
 profile |= vp9_rb_read_bit ( rb ) << 1 ;
 if ( profile > 2 ) profile += vp9_rb_read_bit ( rb ) ;
 return ( BITSTREAM_PROFILE ) profile ;
 }
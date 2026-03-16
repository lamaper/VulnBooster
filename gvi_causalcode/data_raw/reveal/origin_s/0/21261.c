static INTERP_FILTER read_interp_filter ( struct vp9_read_bit_buffer * rb ) {
 const INTERP_FILTER literal_to_filter [ ] = {
 EIGHTTAP_SMOOTH , EIGHTTAP , EIGHTTAP_SHARP , BILINEAR }
 ;
 return vp9_rb_read_bit ( rb ) ? SWITCHABLE : literal_to_filter [ vp9_rb_read_literal ( rb , 2 ) ] ;
 }
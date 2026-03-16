static void setup_loopfilter ( struct loopfilter * lf , struct vp9_read_bit_buffer * rb ) {
 lf -> filter_level = vp9_rb_read_literal ( rb , 6 ) ;
 lf -> sharpness_level = vp9_rb_read_literal ( rb , 3 ) ;
 lf -> mode_ref_delta_update = 0 ;
 lf -> mode_ref_delta_enabled = vp9_rb_read_bit ( rb ) ;
 if ( lf -> mode_ref_delta_enabled ) {
 lf -> mode_ref_delta_update = vp9_rb_read_bit ( rb ) ;
 if ( lf -> mode_ref_delta_update ) {
 int i ;
 for ( i = 0 ;
 i < MAX_REF_LF_DELTAS ;
 i ++ ) if ( vp9_rb_read_bit ( rb ) ) lf -> ref_deltas [ i ] = vp9_rb_read_signed_literal ( rb , 6 ) ;
 for ( i = 0 ;
 i < MAX_MODE_LF_DELTAS ;
 i ++ ) if ( vp9_rb_read_bit ( rb ) ) lf -> mode_deltas [ i ] = vp9_rb_read_signed_literal ( rb , 6 ) ;
 }
 }
 }
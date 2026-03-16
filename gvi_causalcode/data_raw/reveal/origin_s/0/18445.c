static void encode_loopfilter ( struct loopfilter * lf , struct vp9_write_bit_buffer * wb ) {
 int i ;
 vp9_wb_write_literal ( wb , lf -> filter_level , 6 ) ;
 vp9_wb_write_literal ( wb , lf -> sharpness_level , 3 ) ;
 vp9_wb_write_bit ( wb , lf -> mode_ref_delta_enabled ) ;
 if ( lf -> mode_ref_delta_enabled ) {
 vp9_wb_write_bit ( wb , lf -> mode_ref_delta_update ) ;
 if ( lf -> mode_ref_delta_update ) {
 for ( i = 0 ;
 i < MAX_REF_LF_DELTAS ;
 i ++ ) {
 const int delta = lf -> ref_deltas [ i ] ;
 const int changed = delta != lf -> last_ref_deltas [ i ] ;
 vp9_wb_write_bit ( wb , changed ) ;
 if ( changed ) {
 lf -> last_ref_deltas [ i ] = delta ;
 vp9_wb_write_literal ( wb , abs ( delta ) & 0x3F , 6 ) ;
 vp9_wb_write_bit ( wb , delta < 0 ) ;
 }
 }
 for ( i = 0 ;
 i < MAX_MODE_LF_DELTAS ;
 i ++ ) {
 const int delta = lf -> mode_deltas [ i ] ;
 const int changed = delta != lf -> last_mode_deltas [ i ] ;
 vp9_wb_write_bit ( wb , changed ) ;
 if ( changed ) {
 lf -> last_mode_deltas [ i ] = delta ;
 vp9_wb_write_literal ( wb , abs ( delta ) & 0x3F , 6 ) ;
 vp9_wb_write_bit ( wb , delta < 0 ) ;
 }
 }
 }
 }
 }
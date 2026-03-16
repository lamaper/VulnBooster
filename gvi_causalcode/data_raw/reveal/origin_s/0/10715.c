int vp9_rc_pick_q_and_bounds ( const VP9_COMP * cpi , int * bottom_index , int * top_index ) {
 int q ;
 if ( cpi -> oxcf . pass == 0 ) {
 if ( cpi -> oxcf . rc_mode == VPX_CBR ) q = rc_pick_q_and_bounds_one_pass_cbr ( cpi , bottom_index , top_index ) ;
 else q = rc_pick_q_and_bounds_one_pass_vbr ( cpi , bottom_index , top_index ) ;
 }
 else {
 q = rc_pick_q_and_bounds_two_pass ( cpi , bottom_index , top_index ) ;
 }
 if ( cpi -> sf . use_nonrd_pick_mode ) {
 if ( cpi -> sf . force_frame_boost == 1 ) q -= cpi -> sf . max_delta_qindex ;
 if ( q < * bottom_index ) * bottom_index = q ;
 else if ( q > * top_index ) * top_index = q ;
 }
 return q ;
 }
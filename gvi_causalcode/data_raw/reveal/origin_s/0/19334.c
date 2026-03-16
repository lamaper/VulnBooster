void vp9_rc_compute_frame_size_bounds ( const VP9_COMP * cpi , int frame_target , int * frame_under_shoot_limit , int * frame_over_shoot_limit ) {
 if ( cpi -> oxcf . rc_mode == VPX_Q ) {
 * frame_under_shoot_limit = 0 ;
 * frame_over_shoot_limit = INT_MAX ;
 }
 else {
 const int tolerance = ( cpi -> sf . recode_tolerance * frame_target ) / 100 ;
 * frame_under_shoot_limit = MAX ( frame_target - tolerance - 200 , 0 ) ;
 * frame_over_shoot_limit = MIN ( frame_target + tolerance + 200 , cpi -> rc . max_frame_bandwidth ) ;
 }
 }
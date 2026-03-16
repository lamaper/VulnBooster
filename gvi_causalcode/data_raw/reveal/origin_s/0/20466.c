int vp9_rc_clamp_pframe_target_size ( const VP9_COMP * const cpi , int target ) {
 const RATE_CONTROL * rc = & cpi -> rc ;
 const int min_frame_target = MAX ( rc -> min_frame_bandwidth , rc -> avg_frame_bandwidth >> 5 ) ;
 if ( target < min_frame_target ) target = min_frame_target ;
 if ( cpi -> refresh_golden_frame && rc -> is_src_frame_alt_ref ) {
 target = min_frame_target ;
 }
 if ( target > rc -> max_frame_bandwidth ) target = rc -> max_frame_bandwidth ;
 return target ;
 }
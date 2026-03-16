static int get_kf_active_quality ( const RATE_CONTROL * const rc , int q ) {
 return get_active_quality ( q , rc -> kf_boost , kf_low , kf_high , kf_low_motion_minq , kf_high_motion_minq ) ;
 }
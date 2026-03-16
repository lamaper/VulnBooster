static int get_kf_active_quality ( const RATE_CONTROL * const rc , int q , vpx_bit_depth_t bit_depth ) {
 int * kf_low_motion_minq ;
 int * kf_high_motion_minq ;
 ASSIGN_MINQ_TABLE ( bit_depth , kf_low_motion_minq ) ;
 ASSIGN_MINQ_TABLE ( bit_depth , kf_high_motion_minq ) ;
 return get_active_quality ( q , rc -> kf_boost , kf_low , kf_high , kf_low_motion_minq , kf_high_motion_minq ) ;
 }
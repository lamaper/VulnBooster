static int get_gf_active_quality ( const RATE_CONTROL * const rc , int q , vpx_bit_depth_t bit_depth ) {
 int * arfgf_low_motion_minq ;
 int * arfgf_high_motion_minq ;
 ASSIGN_MINQ_TABLE ( bit_depth , arfgf_low_motion_minq ) ;
 ASSIGN_MINQ_TABLE ( bit_depth , arfgf_high_motion_minq ) ;
 return get_active_quality ( q , rc -> gfu_boost , gf_low , gf_high , arfgf_low_motion_minq , arfgf_high_motion_minq ) ;
 }
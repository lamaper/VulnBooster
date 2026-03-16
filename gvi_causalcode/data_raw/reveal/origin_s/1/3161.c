static int get_gf_active_quality ( const RATE_CONTROL * const rc , int q ) {
 return get_active_quality ( q , rc -> gfu_boost , gf_low , gf_high , arfgf_low_motion_minq , arfgf_high_motion_minq ) ;
 }
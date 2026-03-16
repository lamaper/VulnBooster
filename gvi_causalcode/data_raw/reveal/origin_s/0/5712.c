static double get_rate_correction_factor ( const VP9_COMP * cpi ) {
 const RATE_CONTROL * const rc = & cpi -> rc ;
 if ( cpi -> common . frame_type == KEY_FRAME ) {
 return rc -> rate_correction_factors [ KF_STD ] ;
 }
 else if ( cpi -> oxcf . pass == 2 ) {
 RATE_FACTOR_LEVEL rf_lvl = cpi -> twopass . gf_group . rf_level [ cpi -> twopass . gf_group . index ] ;
 return rc -> rate_correction_factors [ rf_lvl ] ;
 }
 else {
 if ( ( cpi -> refresh_alt_ref_frame || cpi -> refresh_golden_frame ) && ! rc -> is_src_frame_alt_ref && ! ( cpi -> use_svc && cpi -> oxcf . rc_mode == VPX_CBR ) ) return rc -> rate_correction_factors [ GF_ARF_STD ] ;
 else return rc -> rate_correction_factors [ INTER_NORMAL ] ;
 }
 }
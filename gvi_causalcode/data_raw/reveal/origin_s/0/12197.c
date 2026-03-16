static int get_twopass_worst_quality ( const VP9_COMP * cpi , const FIRSTPASS_STATS * stats , int section_target_bandwidth ) {
 const RATE_CONTROL * const rc = & cpi -> rc ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 if ( section_target_bandwidth <= 0 ) {
 return rc -> worst_quality ;
 }
 else {
 const int num_mbs = cpi -> common . MBs ;
 const double section_err = stats -> coded_error / stats -> count ;
 const double err_per_mb = section_err / num_mbs ;
 const double speed_term = 1.0 + 0.04 * oxcf -> speed ;
 const int target_norm_bits_per_mb = ( ( uint64_t ) section_target_bandwidth << BPER_MB_NORMBITS ) / num_mbs ;
 int q ;
 int is_svc_upper_layer = 0 ;
 if ( is_two_pass_svc ( cpi ) && cpi -> svc . spatial_layer_id > 0 ) is_svc_upper_layer = 1 ;
 for ( q = rc -> best_quality ;
 q < rc -> worst_quality ;
 ++ q ) {
 const double factor = calc_correction_factor ( err_per_mb , ERR_DIVISOR , is_svc_upper_layer ? SVC_FACTOR_PT_LOW : FACTOR_PT_LOW , FACTOR_PT_HIGH , q , cpi -> common . bit_depth ) ;
 const int bits_per_mb = vp9_rc_bits_per_mb ( INTER_FRAME , q , factor * speed_term , cpi -> common . bit_depth ) ;
 if ( bits_per_mb <= target_norm_bits_per_mb ) break ;
 }
 if ( cpi -> oxcf . rc_mode == VPX_CQ ) q = MAX ( q , oxcf -> cq_level ) ;
 return q ;
 }
 }
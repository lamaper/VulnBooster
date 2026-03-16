static int recode_loop_test ( const VP9_COMP * cpi , int high_limit , int low_limit , int q , int maxq , int minq ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 const RATE_CONTROL * const rc = & cpi -> rc ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 int force_recode = 0 ;
 if ( rc -> projected_frame_size > rc -> max_frame_bandwidth ) {
 force_recode = 1 ;
 }
 else if ( ( cpi -> sf . recode_loop == ALLOW_RECODE ) || ( ( cpi -> sf . recode_loop == ALLOW_RECODE_KFARFGF ) && ( cm -> frame_type == KEY_FRAME || cpi -> refresh_golden_frame || cpi -> refresh_alt_ref_frame ) ) ) {
 if ( ( rc -> projected_frame_size > high_limit && q < maxq ) || ( rc -> projected_frame_size < low_limit && q > minq ) ) {
 force_recode = 1 ;
 }
 else if ( cpi -> oxcf . rc_mode == VPX_CQ ) {
 if ( q > oxcf -> cq_level && rc -> projected_frame_size < ( ( rc -> this_frame_target * 7 ) >> 3 ) ) {
 force_recode = 1 ;
 }
 }
 }
 return force_recode ;
 }
static int recode_loop_test ( VP8_COMP * cpi , int high_limit , int low_limit , int q , int maxq , int minq ) {
 int force_recode = 0 ;
 VP8_COMMON * cm = & cpi -> common ;
 if ( ( cpi -> sf . recode_loop == 1 ) || ( ( cpi -> sf . recode_loop == 2 ) && ( ( cm -> frame_type == KEY_FRAME ) || cm -> refresh_golden_frame || cm -> refresh_alt_ref_frame ) ) ) {
 if ( ( ( cpi -> projected_frame_size > high_limit ) && ( q < maxq ) ) || ( ( cpi -> projected_frame_size < low_limit ) && ( q > minq ) ) ) {
 force_recode = 1 ;
 }
 else if ( cpi -> oxcf . end_usage == USAGE_CONSTRAINED_QUALITY ) {
 if ( ( q > cpi -> cq_target_quality ) && ( cpi -> projected_frame_size < ( ( cpi -> this_frame_target * 7 ) >> 3 ) ) ) {
 force_recode = 1 ;
 }
 else if ( ( q > cpi -> oxcf . cq_level ) && ( cpi -> projected_frame_size < cpi -> min_frame_bandwidth ) && ( cpi -> active_best_quality > cpi -> oxcf . cq_level ) ) {
 force_recode = 1 ;
 cpi -> active_best_quality = cpi -> oxcf . cq_level ;
 }
 }
 }
 return force_recode ;
 }
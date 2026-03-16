void vp9_rc_set_frame_target ( VP9_COMP * cpi , int target ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 rc -> this_frame_target = target ;
 rc -> sb64_target_rate = ( ( int64_t ) rc -> this_frame_target * 64 * 64 ) / ( cm -> width * cm -> height ) ;
 }
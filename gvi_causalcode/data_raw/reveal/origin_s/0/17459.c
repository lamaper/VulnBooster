static int calc_active_worst_quality_one_pass_vbr ( const VP9_COMP * cpi ) {
 const RATE_CONTROL * const rc = & cpi -> rc ;
 const unsigned int curr_frame = cpi -> common . current_video_frame ;
 int active_worst_quality ;
 if ( cpi -> common . frame_type == KEY_FRAME ) {
 active_worst_quality = curr_frame == 0 ? rc -> worst_quality : rc -> last_q [ KEY_FRAME ] * 2 ;
 }
 else {
 if ( ! rc -> is_src_frame_alt_ref && ( cpi -> refresh_golden_frame || cpi -> refresh_alt_ref_frame ) ) {
 active_worst_quality = curr_frame == 1 ? rc -> last_q [ KEY_FRAME ] * 5 / 4 : rc -> last_q [ INTER_FRAME ] ;
 }
 else {
 active_worst_quality = curr_frame == 1 ? rc -> last_q [ KEY_FRAME ] * 2 : rc -> last_q [ INTER_FRAME ] * 2 ;
 }
 }
 return MIN ( active_worst_quality , rc -> worst_quality ) ;
 }
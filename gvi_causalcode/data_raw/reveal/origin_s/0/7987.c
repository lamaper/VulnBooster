void vp9_rc_get_one_pass_cbr_params ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 int target ;
 if ( ( cm -> current_video_frame == 0 || ( cpi -> frame_flags & FRAMEFLAGS_KEY ) || rc -> frames_to_key == 0 || ( cpi -> oxcf . auto_key && 0 ) ) ) {
 cm -> frame_type = KEY_FRAME ;
 rc -> this_key_frame_forced = cm -> current_video_frame != 0 && rc -> frames_to_key == 0 ;
 rc -> frames_to_key = cpi -> oxcf . key_freq ;
 rc -> kf_boost = DEFAULT_KF_BOOST ;
 rc -> source_alt_ref_active = 0 ;
 target = calc_iframe_target_size_one_pass_cbr ( cpi ) ;
 }
 else {
 cm -> frame_type = INTER_FRAME ;
 target = calc_pframe_target_size_one_pass_cbr ( cpi ) ;
 }
 vp9_rc_set_frame_target ( cpi , target ) ;
 rc -> frames_till_gf_update_due = INT_MAX ;
 rc -> baseline_gf_interval = INT_MAX ;
 }
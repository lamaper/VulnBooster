void vp9_rc_get_one_pass_vbr_params ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 int target ;
 if ( ! cpi -> refresh_alt_ref_frame && ( cm -> current_video_frame == 0 || ( cpi -> frame_flags & FRAMEFLAGS_KEY ) || rc -> frames_to_key == 0 || ( cpi -> oxcf . auto_key && 0 ) ) ) {
 cm -> frame_type = KEY_FRAME ;
 rc -> this_key_frame_forced = cm -> current_video_frame != 0 && rc -> frames_to_key == 0 ;
 rc -> frames_to_key = cpi -> oxcf . key_freq ;
 rc -> kf_boost = DEFAULT_KF_BOOST ;
 rc -> source_alt_ref_active = 0 ;
 }
 else {
 cm -> frame_type = INTER_FRAME ;
 }
 if ( rc -> frames_till_gf_update_due == 0 ) {
 rc -> baseline_gf_interval = DEFAULT_GF_INTERVAL ;
 rc -> frames_till_gf_update_due = rc -> baseline_gf_interval ;
 if ( rc -> frames_till_gf_update_due > rc -> frames_to_key ) rc -> frames_till_gf_update_due = rc -> frames_to_key ;
 cpi -> refresh_golden_frame = 1 ;
 rc -> source_alt_ref_pending = USE_ALTREF_FOR_ONE_PASS ;
 rc -> gfu_boost = DEFAULT_GF_BOOST ;
 }
 if ( cm -> frame_type == KEY_FRAME ) target = calc_iframe_target_size_one_pass_vbr ( cpi ) ;
 else target = calc_pframe_target_size_one_pass_vbr ( cpi ) ;
 vp9_rc_set_frame_target ( cpi , target ) ;
 }
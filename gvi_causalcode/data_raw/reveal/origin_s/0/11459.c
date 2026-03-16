void vp9_rc_get_svc_params ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 int target = rc -> avg_frame_bandwidth ;
 if ( ( cm -> current_video_frame == 0 ) || ( cpi -> frame_flags & FRAMEFLAGS_KEY ) || ( cpi -> oxcf . auto_key && ( rc -> frames_since_key % cpi -> oxcf . key_freq == 0 ) ) ) {
 cm -> frame_type = KEY_FRAME ;
 rc -> source_alt_ref_active = 0 ;
 if ( is_two_pass_svc ( cpi ) ) {
 cpi -> svc . layer_context [ cpi -> svc . spatial_layer_id ] . is_key_frame = 1 ;
 cpi -> ref_frame_flags &= ( ~ VP9_LAST_FLAG & ~ VP9_GOLD_FLAG & ~ VP9_ALT_FLAG ) ;
 }
 if ( cpi -> oxcf . pass == 0 && cpi -> oxcf . rc_mode == VPX_CBR ) {
 target = calc_iframe_target_size_one_pass_cbr ( cpi ) ;
 }
 }
 else {
 cm -> frame_type = INTER_FRAME ;
 if ( is_two_pass_svc ( cpi ) ) {
 LAYER_CONTEXT * lc = & cpi -> svc . layer_context [ cpi -> svc . spatial_layer_id ] ;
 if ( cpi -> svc . spatial_layer_id == 0 ) {
 lc -> is_key_frame = 0 ;
 }
 else {
 lc -> is_key_frame = cpi -> svc . layer_context [ 0 ] . is_key_frame ;
 if ( lc -> is_key_frame ) cpi -> ref_frame_flags &= ( ~ VP9_LAST_FLAG ) ;
 }
 cpi -> ref_frame_flags &= ( ~ VP9_ALT_FLAG ) ;
 }
 if ( cpi -> oxcf . pass == 0 && cpi -> oxcf . rc_mode == VPX_CBR ) {
 target = calc_pframe_target_size_one_pass_cbr ( cpi ) ;
 }
 }
 vp9_rc_set_frame_target ( cpi , target ) ;
 rc -> frames_till_gf_update_due = INT_MAX ;
 rc -> baseline_gf_interval = INT_MAX ;
 }
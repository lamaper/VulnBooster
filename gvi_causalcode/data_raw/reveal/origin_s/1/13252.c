void vp9_rc_get_second_pass_params ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 TWO_PASS * const twopass = & cpi -> twopass ;
 GF_GROUP * const gf_group = & twopass -> gf_group ;
 int frames_left ;
 FIRSTPASS_STATS this_frame ;
 FIRSTPASS_STATS this_frame_copy ;
 int target_rate ;
 LAYER_CONTEXT * const lc = is_two_pass_svc ( cpi ) ? & cpi -> svc . layer_context [ cpi -> svc . spatial_layer_id ] : 0 ;
 if ( lc != NULL ) {
 frames_left = ( int ) ( twopass -> total_stats . count - lc -> current_video_frame_in_layer ) ;
 }
 else {
 frames_left = ( int ) ( twopass -> total_stats . count - cm -> current_video_frame ) ;
 }
 if ( ! twopass -> stats_in ) return ;
 if ( gf_group -> update_type [ gf_group -> index ] == ARF_UPDATE ) {
 int target_rate ;
 configure_buffer_updates ( cpi ) ;
 target_rate = gf_group -> bit_allocation [ gf_group -> index ] ;
 target_rate = vp9_rc_clamp_pframe_target_size ( cpi , target_rate ) ;
 rc -> base_frame_target = target_rate ;
 if ( cpi -> oxcf . rc_mode == VPX_VBR ) vbr_rate_correction ( & target_rate , rc -> vbr_bits_off_target ) ;
 vp9_rc_set_frame_target ( cpi , target_rate ) ;
 cm -> frame_type = INTER_FRAME ;
 if ( lc != NULL ) {
 if ( cpi -> svc . spatial_layer_id == 0 ) {
 lc -> is_key_frame = 0 ;
 }
 else {
 lc -> is_key_frame = cpi -> svc . layer_context [ 0 ] . is_key_frame ;
 if ( lc -> is_key_frame ) cpi -> ref_frame_flags &= ( ~ VP9_LAST_FLAG ) ;
 }
 }
 return ;
 }
 vp9_clear_system_state ( ) ;
 if ( lc != NULL && twopass -> kf_intra_err_min == 0 ) {
 twopass -> kf_intra_err_min = KF_MB_INTRA_MIN * cpi -> common . MBs ;
 twopass -> gf_intra_err_min = GF_MB_INTRA_MIN * cpi -> common . MBs ;
 }
 if ( cpi -> oxcf . rc_mode == VPX_Q ) {
 twopass -> active_worst_quality = cpi -> oxcf . cq_level ;
 }
 else if ( cm -> current_video_frame == 0 || ( lc != NULL && lc -> current_video_frame_in_layer == 0 ) ) {
 const int section_target_bandwidth = ( int ) ( twopass -> bits_left / frames_left ) ;
 const int tmp_q = get_twopass_worst_quality ( cpi , & twopass -> total_left_stats , section_target_bandwidth ) ;
 twopass -> active_worst_quality = tmp_q ;
 rc -> ni_av_qi = tmp_q ;
 rc -> avg_q = vp9_convert_qindex_to_q ( tmp_q ) ;
 }
 vp9_zero ( this_frame ) ;
 if ( EOF == input_stats ( twopass , & this_frame ) ) return ;
 this_frame_copy = this_frame ;
 if ( rc -> frames_to_key == 0 || ( cpi -> frame_flags & FRAMEFLAGS_KEY ) ) {
 find_next_key_frame ( cpi , & this_frame_copy ) ;
 }
 else {
 cm -> frame_type = INTER_FRAME ;
 }
 if ( lc != NULL ) {
 if ( cpi -> svc . spatial_layer_id == 0 ) {
 lc -> is_key_frame = ( cm -> frame_type == KEY_FRAME ) ;
 if ( lc -> is_key_frame ) {
 cpi -> ref_frame_flags &= ( ~ VP9_LAST_FLAG & ~ VP9_GOLD_FLAG & ~ VP9_ALT_FLAG ) ;
 lc -> frames_from_key_frame = 0 ;
 }
 }
 else {
 cm -> frame_type = INTER_FRAME ;
 lc -> is_key_frame = cpi -> svc . layer_context [ 0 ] . is_key_frame ;
 if ( lc -> is_key_frame ) {
 cpi -> ref_frame_flags &= ( ~ VP9_LAST_FLAG ) ;
 lc -> frames_from_key_frame = 0 ;
 }
 }
 }
 if ( rc -> frames_till_gf_update_due == 0 ) {
 define_gf_group ( cpi , & this_frame_copy ) ;
 if ( twopass -> gf_zeromotion_pct > 995 ) {
 if ( ! cm -> show_frame ) cpi -> allow_encode_breakout = ENCODE_BREAKOUT_DISABLED ;
 else cpi -> allow_encode_breakout = ENCODE_BREAKOUT_LIMITED ;
 }
 rc -> frames_till_gf_update_due = rc -> baseline_gf_interval ;
 if ( lc != NULL ) cpi -> refresh_golden_frame = 1 ;
 }
 configure_buffer_updates ( cpi ) ;
 target_rate = gf_group -> bit_allocation [ gf_group -> index ] ;
 if ( cpi -> common . frame_type == KEY_FRAME ) target_rate = vp9_rc_clamp_iframe_target_size ( cpi , target_rate ) ;
 else target_rate = vp9_rc_clamp_pframe_target_size ( cpi , target_rate ) ;
 rc -> base_frame_target = target_rate ;
 if ( cpi -> oxcf . rc_mode == VPX_VBR ) vbr_rate_correction ( & target_rate , rc -> vbr_bits_off_target ) ;
 vp9_rc_set_frame_target ( cpi , target_rate ) ;
 subtract_stats ( & twopass -> total_left_stats , & this_frame ) ;
 }
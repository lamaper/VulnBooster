void vp9_rc_postencode_update ( VP9_COMP * cpi , uint64_t bytes_used ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 const int qindex = cm -> base_qindex ;
 rc -> projected_frame_size = ( int ) ( bytes_used << 3 ) ;
 vp9_rc_update_rate_correction_factors ( cpi , ( cpi -> sf . recode_loop >= ALLOW_RECODE_KFARFGF || oxcf -> rc_mode == VPX_CBR ) ? 2 : 0 ) ;
 if ( cm -> frame_type == KEY_FRAME ) {
 rc -> last_q [ KEY_FRAME ] = qindex ;
 rc -> avg_frame_qindex [ KEY_FRAME ] = ROUND_POWER_OF_TWO ( 3 * rc -> avg_frame_qindex [ KEY_FRAME ] + qindex , 2 ) ;
 }
 else {
 if ( rc -> is_src_frame_alt_ref || ! ( cpi -> refresh_golden_frame || cpi -> refresh_alt_ref_frame ) || ( cpi -> use_svc && oxcf -> rc_mode == VPX_CBR ) ) {
 rc -> last_q [ INTER_FRAME ] = qindex ;
 rc -> avg_frame_qindex [ INTER_FRAME ] = ROUND_POWER_OF_TWO ( 3 * rc -> avg_frame_qindex [ INTER_FRAME ] + qindex , 2 ) ;
 rc -> ni_frames ++ ;
 rc -> tot_q += vp9_convert_qindex_to_q ( qindex , cm -> bit_depth ) ;
 rc -> avg_q = rc -> tot_q / rc -> ni_frames ;
 rc -> ni_tot_qi += qindex ;
 rc -> ni_av_qi = rc -> ni_tot_qi / rc -> ni_frames ;
 }
 }
 if ( ( qindex < rc -> last_boosted_qindex ) || ( ( ( cm -> frame_type == KEY_FRAME ) || cpi -> refresh_alt_ref_frame || ( cpi -> refresh_golden_frame && ! rc -> is_src_frame_alt_ref ) ) ) ) {
 rc -> last_boosted_qindex = qindex ;
 }
 if ( cm -> frame_type == KEY_FRAME ) rc -> last_kf_qindex = qindex ;
 update_buffer_level ( cpi , rc -> projected_frame_size ) ;
 if ( cm -> frame_type != KEY_FRAME ) {
 rc -> rolling_target_bits = ROUND_POWER_OF_TWO ( rc -> rolling_target_bits * 3 + rc -> this_frame_target , 2 ) ;
 rc -> rolling_actual_bits = ROUND_POWER_OF_TWO ( rc -> rolling_actual_bits * 3 + rc -> projected_frame_size , 2 ) ;
 rc -> long_rolling_target_bits = ROUND_POWER_OF_TWO ( rc -> long_rolling_target_bits * 31 + rc -> this_frame_target , 5 ) ;
 rc -> long_rolling_actual_bits = ROUND_POWER_OF_TWO ( rc -> long_rolling_actual_bits * 31 + rc -> projected_frame_size , 5 ) ;
 }
 rc -> total_actual_bits += rc -> projected_frame_size ;
 rc -> total_target_bits += cm -> show_frame ? rc -> avg_frame_bandwidth : 0 ;
 rc -> total_target_vs_actual = rc -> total_actual_bits - rc -> total_target_bits ;
 if ( is_altref_enabled ( cpi ) && cpi -> refresh_alt_ref_frame && ( cm -> frame_type != KEY_FRAME ) ) update_alt_ref_frame_stats ( cpi ) ;
 else update_golden_frame_stats ( cpi ) ;
 if ( cm -> frame_type == KEY_FRAME ) rc -> frames_since_key = 0 ;
 if ( cm -> show_frame ) {
 rc -> frames_since_key ++ ;
 rc -> frames_to_key -- ;
 }
 }
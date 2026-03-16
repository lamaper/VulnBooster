static void define_gf_group ( VP9_COMP * cpi , FIRSTPASS_STATS * this_frame ) {
 RATE_CONTROL * const rc = & cpi -> rc ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 TWO_PASS * const twopass = & cpi -> twopass ;
 FIRSTPASS_STATS next_frame ;
 const FIRSTPASS_STATS * const start_pos = twopass -> stats_in ;
 int i ;
 double boost_score = 0.0 ;
 double old_boost_score = 0.0 ;
 double gf_group_err = 0.0 ;
 double gf_first_frame_err = 0.0 ;
 double mod_frame_err = 0.0 ;
 double mv_ratio_accumulator = 0.0 ;
 double decay_accumulator = 1.0 ;
 double zero_motion_accumulator = 1.0 ;
 double loop_decay_rate = 1.00 ;
 double last_loop_decay_rate = 1.00 ;
 double this_frame_mv_in_out = 0.0 ;
 double mv_in_out_accumulator = 0.0 ;
 double abs_mv_in_out_accumulator = 0.0 ;
 double mv_ratio_accumulator_thresh ;
 unsigned int allow_alt_ref = is_altref_enabled ( cpi ) ;
 int f_boost = 0 ;
 int b_boost = 0 ;
 int flash_detected ;
 int active_max_gf_interval ;
 int64_t gf_group_bits ;
 double gf_group_error_left ;
 int gf_arf_bits ;
 if ( cpi -> common . frame_type != KEY_FRAME ) {
 vp9_zero ( twopass -> gf_group ) ;
 }
 vp9_clear_system_state ( ) ;
 vp9_zero ( next_frame ) ;
 mod_frame_err = calculate_modified_err ( twopass , oxcf , this_frame ) ;
 gf_first_frame_err = mod_frame_err ;
 if ( cpi -> common . frame_type == KEY_FRAME || rc -> source_alt_ref_active ) gf_group_err -= gf_first_frame_err ;
 mv_ratio_accumulator_thresh = ( cpi -> common . width + cpi -> common . height ) / 4.0 ;
 if ( cpi -> multi_arf_allowed ) {
 active_max_gf_interval = rc -> max_gf_interval ;
 }
 else {
 active_max_gf_interval = + ( ( int ) vp9_convert_qindex_to_q ( rc -> last_q [ INTER_FRAME ] , cpi -> common . bit_depth ) >> 5 ) ;
 if ( active_max_gf_interval > rc -> max_gf_interval ) active_max_gf_interval = rc -> max_gf_interval ;
 }
 i = 0 ;
 while ( i < rc -> static_scene_max_gf_interval && i < rc -> frames_to_key ) {
 ++ i ;
 mod_frame_err = calculate_modified_err ( twopass , oxcf , this_frame ) ;
 gf_group_err += mod_frame_err ;
 if ( EOF == input_stats ( twopass , & next_frame ) ) break ;
 flash_detected = detect_flash ( twopass , 0 ) ;
 accumulate_frame_motion_stats ( & next_frame , & this_frame_mv_in_out , & mv_in_out_accumulator , & abs_mv_in_out_accumulator , & mv_ratio_accumulator ) ;
 if ( ! flash_detected ) {
 last_loop_decay_rate = loop_decay_rate ;
 loop_decay_rate = get_prediction_decay_rate ( & cpi -> common , & next_frame ) ;
 decay_accumulator = decay_accumulator * loop_decay_rate ;
 zero_motion_accumulator = MIN ( zero_motion_accumulator , get_zero_motion_factor ( & cpi -> common , & next_frame ) ) ;
 if ( detect_transition_to_still ( twopass , i , 5 , loop_decay_rate , last_loop_decay_rate ) ) {
 allow_alt_ref = 0 ;
 break ;
 }
 }
 boost_score += decay_accumulator * calc_frame_boost ( cpi , & next_frame , this_frame_mv_in_out , GF_MAX_BOOST ) ;
 if ( ( i >= active_max_gf_interval && ( zero_motion_accumulator < 0.995 ) ) || ( ( i > MIN_GF_INTERVAL ) && ( ! flash_detected ) && ( ( mv_ratio_accumulator > mv_ratio_accumulator_thresh ) || ( abs_mv_in_out_accumulator > 3.0 ) || ( mv_in_out_accumulator < - 2.0 ) || ( ( boost_score - old_boost_score ) < BOOST_FACTOR ) ) ) ) {
 boost_score = old_boost_score ;
 break ;
 }
 * this_frame = next_frame ;
 old_boost_score = boost_score ;
 }
 twopass -> gf_zeromotion_pct = ( int ) ( zero_motion_accumulator * 1000.0 ) ;
 if ( cpi -> common . frame_type == KEY_FRAME || rc -> source_alt_ref_active ) rc -> baseline_gf_interval = i - 1 ;
 else rc -> baseline_gf_interval = i ;
 if ( is_two_pass_svc ( cpi ) && cpi -> svc . number_temporal_layers > 1 ) {
 int count = ( 1 << ( cpi -> svc . number_temporal_layers - 1 ) ) - 1 ;
 int new_gf_interval = ( rc -> baseline_gf_interval + count ) & ( ~ count ) ;
 int j ;
 for ( j = 0 ;
 j < new_gf_interval - rc -> baseline_gf_interval ;
 ++ j ) {
 if ( EOF == input_stats ( twopass , this_frame ) ) break ;
 gf_group_err += calculate_modified_err ( twopass , oxcf , this_frame ) ;
 }
 rc -> baseline_gf_interval = new_gf_interval ;
 }
 rc -> frames_till_gf_update_due = rc -> baseline_gf_interval ;
 if ( allow_alt_ref && ( i < cpi -> oxcf . lag_in_frames ) && ( i >= MIN_GF_INTERVAL ) ) {
 rc -> gfu_boost = calc_arf_boost ( cpi , 0 , ( i - 1 ) , ( i - 1 ) , & f_boost , & b_boost ) ;
 rc -> source_alt_ref_pending = 1 ;
 cpi -> multi_arf_enabled = ( cpi -> multi_arf_allowed && ( rc -> baseline_gf_interval >= 6 ) && ( zero_motion_accumulator < 0.995 ) ) ? 1 : 0 ;
 }
 else {
 rc -> gfu_boost = MAX ( ( int ) boost_score , 125 ) ;
 rc -> source_alt_ref_pending = 0 ;
 }
 reset_fpf_position ( twopass , start_pos ) ;
 gf_group_bits = calculate_total_gf_group_bits ( cpi , gf_group_err ) ;
 {
 int q = rc -> last_q [ INTER_FRAME ] ;
 int boost = ( rc -> gfu_boost * gfboost_qadjust ( q , cpi -> common . bit_depth ) ) / 100 ;
 boost = clamp ( boost , 125 , ( rc -> baseline_gf_interval + 1 ) * 200 ) ;
 gf_arf_bits = calculate_boost_bits ( rc -> baseline_gf_interval , boost , gf_group_bits ) ;
 }
 twopass -> kf_group_error_left -= ( int64_t ) gf_group_err ;
 if ( rc -> source_alt_ref_pending ) {
 gf_group_error_left = gf_group_err - mod_frame_err ;
 }
 else if ( cpi -> common . frame_type != KEY_FRAME ) {
 gf_group_error_left = gf_group_err - gf_first_frame_err ;
 }
 else {
 gf_group_error_left = gf_group_err ;
 }
 allocate_gf_group_bits ( cpi , gf_group_bits , gf_group_error_left , gf_arf_bits ) ;
 reset_fpf_position ( twopass , start_pos ) ;
 if ( cpi -> common . frame_type != KEY_FRAME ) {
 twopass -> section_intra_rating = calculate_section_intra_ratio ( start_pos , twopass -> stats_in_end , rc -> baseline_gf_interval ) ;
 }
 }
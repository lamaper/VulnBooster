static void find_next_key_frame ( VP9_COMP * cpi , FIRSTPASS_STATS * this_frame ) {
 int i , j ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 TWO_PASS * const twopass = & cpi -> twopass ;
 GF_GROUP * const gf_group = & twopass -> gf_group ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 const FIRSTPASS_STATS first_frame = * this_frame ;
 const FIRSTPASS_STATS * const start_position = twopass -> stats_in ;
 FIRSTPASS_STATS next_frame ;
 FIRSTPASS_STATS last_frame ;
 int kf_bits = 0 ;
 double decay_accumulator = 1.0 ;
 double zero_motion_accumulator = 1.0 ;
 double boost_score = 0.0 ;
 double kf_mod_err = 0.0 ;
 double kf_group_err = 0.0 ;
 double recent_loop_decay [ 8 ] = {
 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 }
 ;
 vp9_zero ( next_frame ) ;
 cpi -> common . frame_type = KEY_FRAME ;
 vp9_zero ( * gf_group ) ;
 rc -> this_key_frame_forced = rc -> next_key_frame_forced ;
 rc -> source_alt_ref_active = 0 ;
 cpi -> multi_arf_last_grp_enabled = 0 ;
 rc -> frames_till_gf_update_due = 0 ;
 rc -> frames_to_key = 1 ;
 twopass -> kf_group_bits = 0 ;
 twopass -> kf_group_error_left = 0 ;
 kf_mod_err = calculate_modified_err ( twopass , oxcf , this_frame ) ;
 i = 0 ;
 while ( twopass -> stats_in < twopass -> stats_in_end && rc -> frames_to_key < cpi -> oxcf . key_freq ) {
 kf_group_err += calculate_modified_err ( twopass , oxcf , this_frame ) ;
 last_frame = * this_frame ;
 input_stats ( twopass , this_frame ) ;
 if ( cpi -> oxcf . auto_key && twopass -> stats_in < twopass -> stats_in_end ) {
 double loop_decay_rate ;
 if ( test_candidate_kf ( twopass , & last_frame , this_frame , twopass -> stats_in ) ) break ;
 loop_decay_rate = get_prediction_decay_rate ( & cpi -> common , twopass -> stats_in ) ;
 recent_loop_decay [ i % 8 ] = loop_decay_rate ;
 decay_accumulator = 1.0 ;
 for ( j = 0 ;
 j < 8 ;
 ++ j ) decay_accumulator *= recent_loop_decay [ j ] ;
 if ( detect_transition_to_still ( twopass , i , cpi -> oxcf . key_freq - i , loop_decay_rate , decay_accumulator ) ) break ;
 ++ rc -> frames_to_key ;
 if ( rc -> frames_to_key >= 2 * cpi -> oxcf . key_freq ) break ;
 }
 else {
 ++ rc -> frames_to_key ;
 }
 ++ i ;
 }
 if ( cpi -> oxcf . auto_key && rc -> frames_to_key > cpi -> oxcf . key_freq ) {
 FIRSTPASS_STATS tmp_frame = first_frame ;
 rc -> frames_to_key /= 2 ;
 reset_fpf_position ( twopass , start_position ) ;
 kf_group_err = 0 ;
 for ( i = 0 ;
 i < rc -> frames_to_key ;
 ++ i ) {
 kf_group_err += calculate_modified_err ( twopass , oxcf , & tmp_frame ) ;
 input_stats ( twopass , & tmp_frame ) ;
 }
 rc -> next_key_frame_forced = 1 ;
 }
 else if ( twopass -> stats_in == twopass -> stats_in_end || rc -> frames_to_key >= cpi -> oxcf . key_freq ) {
 rc -> next_key_frame_forced = 1 ;
 }
 else {
 rc -> next_key_frame_forced = 0 ;
 }
 if ( is_two_pass_svc ( cpi ) && cpi -> svc . number_temporal_layers > 1 ) {
 int count = ( 1 << ( cpi -> svc . number_temporal_layers - 1 ) ) - 1 ;
 int new_frame_to_key = ( rc -> frames_to_key + count ) & ( ~ count ) ;
 int j ;
 for ( j = 0 ;
 j < new_frame_to_key - rc -> frames_to_key ;
 ++ j ) {
 if ( EOF == input_stats ( twopass , this_frame ) ) break ;
 kf_group_err += calculate_modified_err ( twopass , oxcf , this_frame ) ;
 }
 rc -> frames_to_key = new_frame_to_key ;
 }
 if ( twopass -> stats_in >= twopass -> stats_in_end ) {
 kf_group_err += calculate_modified_err ( twopass , oxcf , this_frame ) ;
 }
 if ( twopass -> bits_left > 0 && twopass -> modified_error_left > 0.0 ) {
 const int max_bits = frame_max_bits ( rc , & cpi -> oxcf ) ;
 int64_t max_grp_bits ;
 twopass -> kf_group_bits = ( int64_t ) ( twopass -> bits_left * ( kf_group_err / twopass -> modified_error_left ) ) ;
 max_grp_bits = ( int64_t ) max_bits * ( int64_t ) rc -> frames_to_key ;
 if ( twopass -> kf_group_bits > max_grp_bits ) twopass -> kf_group_bits = max_grp_bits ;
 }
 else {
 twopass -> kf_group_bits = 0 ;
 }
 twopass -> kf_group_bits = MAX ( 0 , twopass -> kf_group_bits ) ;
 reset_fpf_position ( twopass , start_position ) ;
 decay_accumulator = 1.0 ;
 boost_score = 0.0 ;
 for ( i = 0 ;
 i < rc -> frames_to_key ;
 ++ i ) {
 if ( EOF == input_stats ( twopass , & next_frame ) ) break ;
 zero_motion_accumulator = MIN ( zero_motion_accumulator , get_zero_motion_factor ( & next_frame ) ) ;
 if ( i <= ( rc -> max_gf_interval * 2 ) ) {
 double r ;
 if ( next_frame . intra_error > twopass -> kf_intra_err_min ) r = ( IIKFACTOR2 * next_frame . intra_error / DOUBLE_DIVIDE_CHECK ( next_frame . coded_error ) ) ;
 else r = ( IIKFACTOR2 * twopass -> kf_intra_err_min / DOUBLE_DIVIDE_CHECK ( next_frame . coded_error ) ) ;
 if ( r > RMAX ) r = RMAX ;
 if ( ! detect_flash ( twopass , 0 ) ) {
 const double loop_decay_rate = get_prediction_decay_rate ( & cpi -> common , & next_frame ) ;
 decay_accumulator *= loop_decay_rate ;
 decay_accumulator = MAX ( decay_accumulator , MIN_DECAY_FACTOR ) ;
 }
 boost_score += ( decay_accumulator * r ) ;
 }
 }
 reset_fpf_position ( twopass , start_position ) ;
 twopass -> kf_zeromotion_pct = ( int ) ( zero_motion_accumulator * 100.0 ) ;
 twopass -> section_intra_rating = calculate_section_intra_ratio ( start_position , twopass -> stats_in_end , rc -> frames_to_key ) ;
 rc -> kf_boost = ( int ) boost_score ;
 if ( rc -> kf_boost < ( rc -> frames_to_key * 3 ) ) rc -> kf_boost = ( rc -> frames_to_key * 3 ) ;
 if ( rc -> kf_boost < MIN_KF_BOOST ) rc -> kf_boost = MIN_KF_BOOST ;
 kf_bits = calculate_boost_bits ( ( rc -> frames_to_key - 1 ) , rc -> kf_boost , twopass -> kf_group_bits ) ;
 twopass -> kf_group_bits -= kf_bits ;
 gf_group -> bit_allocation [ 0 ] = kf_bits ;
 gf_group -> update_type [ 0 ] = KF_UPDATE ;
 gf_group -> rf_level [ 0 ] = KF_STD ;
 twopass -> kf_group_error_left = ( int ) ( kf_group_err - kf_mod_err ) ;
 twopass -> modified_error_left -= kf_group_err ;
 }
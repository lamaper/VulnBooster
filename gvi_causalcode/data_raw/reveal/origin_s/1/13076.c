static void encode_frame_to_data_rate ( VP8_COMP * cpi , unsigned long * size , unsigned char * dest , unsigned char * dest_end , unsigned int * frame_flags ) {
 int Q ;
 int frame_over_shoot_limit ;
 int frame_under_shoot_limit ;
 int Loop = 0 ;
 int loop_count ;
 VP8_COMMON * cm = & cpi -> common ;
 int active_worst_qchanged = 0 ;

 int q_high ;
 int zbin_oq_high ;
 int zbin_oq_low = 0 ;
 int top_index ;
 int bottom_index ;
 int overshoot_seen = 0 ;
 int undershoot_seen = 0 ;

 int drop_mark75 = drop_mark * 2 / 3 ;
 int drop_mark50 = drop_mark / 4 ;
 int drop_mark25 = drop_mark / 8 ;
 vp8_clear_system_state ( ) ;

 sem_wait ( & cpi -> h_event_end_lpf ) ;
 cpi -> b_lpf_running = 0 ;
 }

 cm -> frame_type = KEY_FRAME ;
 cpi -> force_next_frame_intra = 0 ;
 }

 if ( cpi -> common . refresh_alt_ref_frame ) {
 cpi -> per_frame_bandwidth = cpi -> twopass . gf_bits ;
 cpi -> target_bandwidth = ( int ) ( cpi -> twopass . gf_bits * cpi -> output_framerate ) ;
 }
 }
 else # endif cpi -> per_frame_bandwidth = ( int ) ( cpi -> target_bandwidth / cpi -> output_framerate ) ;
 cm -> copy_buffer_to_gf = 0 ;
 cm -> copy_buffer_to_arf = 0 ;
 cpi -> mb . zbin_over_quant = 0 ;
 cpi -> mb . zbin_mode_boost = 0 ;
 cpi -> mb . zbin_mode_boost_enabled = 1 ;
 if ( cpi -> pass == 2 ) {
 if ( cpi -> gfu_boost <= 400 ) {
 cpi -> mb . zbin_mode_boost_enabled = 0 ;
 }
 }
 if ( cpi -> source_alt_ref_active ) cpi -> common . ref_frame_sign_bias [ ALTREF_FRAME ] = 1 ;
 else cpi -> common . ref_frame_sign_bias [ ALTREF_FRAME ] = 0 ;
 if ( ( cm -> current_video_frame == 0 ) || ( cm -> frame_flags & FRAMEFLAGS_KEY ) || ( cpi -> oxcf . auto_key && ( cpi -> frames_since_key % cpi -> key_frame_frequency == 0 ) ) ) {
 cm -> frame_type = KEY_FRAME ;

 vp8_denoiser_set_parameters ( & cpi -> denoiser , kDenoiserOnYUV ) ;
 }


 LOWER_RES_FRAME_INFO * low_res_frame_info = ( LOWER_RES_FRAME_INFO * ) cpi -> oxcf . mr_low_res_mode_info ;
 cm -> frame_type = low_res_frame_info -> frame_type ;
 if ( cm -> frame_type != KEY_FRAME ) {
 cpi -> mr_low_res_mv_avail = 1 ;
 cpi -> mr_low_res_mv_avail &= ! ( low_res_frame_info -> is_frame_dropped ) ;
 if ( cpi -> ref_frame_flags & VP8_LAST_FRAME ) cpi -> mr_low_res_mv_avail &= ( cpi -> current_ref_frames [ LAST_FRAME ] == low_res_frame_info -> low_res_ref_frames [ LAST_FRAME ] ) ;
 if ( cpi -> ref_frame_flags & VP8_GOLD_FRAME ) cpi -> mr_low_res_mv_avail &= ( cpi -> current_ref_frames [ GOLDEN_FRAME ] == low_res_frame_info -> low_res_ref_frames [ GOLDEN_FRAME ] ) ;
 if ( cpi -> ref_frame_flags & VP8_ALTR_FRAME ) cpi -> mr_low_res_mv_avail &= ( cpi -> current_ref_frames [ ALTREF_FRAME ] == low_res_frame_info -> low_res_ref_frames [ ALTREF_FRAME ] ) ;
 }
 }

 if ( cm -> frame_type != KEY_FRAME ) {
 int i ;
 MV_REFERENCE_FRAME closest_ref = INTRA_FRAME ;
 if ( cpi -> ref_frame_flags & VP8_LAST_FRAME ) {
 closest_ref = LAST_FRAME ;
 }
 else if ( cpi -> ref_frame_flags & VP8_GOLD_FRAME ) {
 closest_ref = GOLDEN_FRAME ;
 }
 else if ( cpi -> ref_frame_flags & VP8_ALTR_FRAME ) {
 closest_ref = ALTREF_FRAME ;
 }
 for ( i = 1 ;
 i <= 3 ;
 i ++ ) {
 vpx_ref_frame_type_t ref_frame_type = ( vpx_ref_frame_type_t ) ( ( i == 3 ) ? 4 : i ) ;
 if ( cpi -> ref_frame_flags & ref_frame_type ) {
 if ( ( cm -> current_video_frame - cpi -> current_ref_frames [ i ] ) < ( cm -> current_video_frame - cpi -> current_ref_frames [ closest_ref ] ) ) {
 closest_ref = i ;
 }
 }
 }
 cpi -> closest_reference_frame = closest_ref ;
 }
 if ( cm -> frame_type == KEY_FRAME ) {
 int i ;
 setup_features ( cpi ) ;
 cpi -> source_alt_ref_active = 0 ;
 for ( i = 0 ;
 i < MAX_MODES ;
 i ++ ) {
 cpi -> mb . rd_thresh_mult [ i ] = 128 ;
 }
 vpx_memset ( cpi -> consec_zero_last , 0 , cm -> mb_rows * cm -> mb_cols ) ;
 }

 cpi -> one_pass_frame_index = cm -> current_video_frame % MAX_LAG_BUFFERS ;
 cpi -> one_pass_frame_stats [ cpi -> one_pass_frame_index ] . frames_so_far = 0 ;
 cpi -> one_pass_frame_stats [ cpi -> one_pass_frame_index ] . frame_intra_error = 0.0 ;
 cpi -> one_pass_frame_stats [ cpi -> one_pass_frame_index ] . frame_coded_error = 0.0 ;
 cpi -> one_pass_frame_stats [ cpi -> one_pass_frame_index ] . frame_pcnt_inter = 0.0 ;
 cpi -> one_pass_frame_stats [ cpi -> one_pass_frame_index ] . frame_pcnt_motion = 0.0 ;
 cpi -> one_pass_frame_stats [ cpi -> one_pass_frame_index ] . frame_mvr = 0.0 ;
 cpi -> one_pass_frame_stats [ cpi -> one_pass_frame_index ] . frame_mvr_abs = 0.0 ;
 cpi -> one_pass_frame_stats [ cpi -> one_pass_frame_index ] . frame_mvc = 0.0 ;
 cpi -> one_pass_frame_stats [ cpi -> one_pass_frame_index ] . frame_mvc_abs = 0.0 ;
 }

 if ( cpi -> drop_frames_allowed ) {
 if ( ( cpi -> buffer_level > drop_mark ) && ( cpi -> decimation_factor > 0 ) ) cpi -> decimation_factor -- ;
 if ( cpi -> buffer_level > drop_mark75 && cpi -> decimation_factor > 0 ) cpi -> decimation_factor = 1 ;
 else if ( cpi -> buffer_level < drop_mark25 && ( cpi -> decimation_factor == 2 || cpi -> decimation_factor == 3 ) ) {
 cpi -> decimation_factor = 3 ;
 }
 else if ( cpi -> buffer_level < drop_mark50 && ( cpi -> decimation_factor == 1 || cpi -> decimation_factor == 2 ) ) {
 cpi -> decimation_factor = 2 ;
 }
 else if ( cpi -> buffer_level < drop_mark75 && ( cpi -> decimation_factor == 0 || cpi -> decimation_factor == 1 ) ) {
 cpi -> decimation_factor = 1 ;
 }
 }
 if ( cpi -> decimation_factor > 0 ) {
 switch ( cpi -> decimation_factor ) {
 case 1 : cpi -> per_frame_bandwidth = cpi -> per_frame_bandwidth * 3 / 2 ;
 break ;
 case 2 : cpi -> per_frame_bandwidth = cpi -> per_frame_bandwidth * 5 / 4 ;
 break ;
 case 3 : cpi -> per_frame_bandwidth = cpi -> per_frame_bandwidth * 5 / 4 ;
 break ;
 }
 if ( cm -> frame_type == KEY_FRAME ) {
 cpi -> decimation_count = cpi -> decimation_factor ;
 }
 else if ( cpi -> decimation_count > 0 ) {
 cpi -> decimation_count -- ;
 cpi -> bits_off_target += cpi -> av_per_frame_bandwidth ;
 if ( cpi -> bits_off_target > cpi -> oxcf . maximum_buffer_size ) cpi -> bits_off_target = cpi -> oxcf . maximum_buffer_size ;


 cpi -> frames_since_key ++ ;
 cpi -> temporal_pattern_counter ++ ;


 if ( cpi -> oxcf . number_of_layers > 1 ) {
 unsigned int i ;
 for ( i = cpi -> current_layer + 1 ;
 i < cpi -> oxcf . number_of_layers ;
 i ++ ) {
 LAYER_CONTEXT * lc = & cpi -> layer_context [ i ] ;
 lc -> bits_off_target += ( int ) ( lc -> target_bandwidth / lc -> framerate ) ;
 if ( lc -> bits_off_target > lc -> maximum_buffer_size ) lc -> bits_off_target = lc -> maximum_buffer_size ;
 lc -> buffer_level = lc -> bits_off_target ;
 }
 }
 return ;
 }
 else cpi -> decimation_count = cpi -> decimation_factor ;
 }
 else cpi -> decimation_count = 0 ;
 if ( ! vp8_pick_frame_size ( cpi ) ) {


 cpi -> frames_since_key ++ ;
 cpi -> temporal_pattern_counter ++ ;
 return ;
 }
 if ( ( cpi -> oxcf . end_usage == USAGE_STREAM_FROM_SERVER ) && ( cpi -> buffer_level >= cpi -> oxcf . optimal_buffer_level ) && cpi -> buffered_mode ) {
 int Adjustment = cpi -> active_worst_quality / 4 ;
 if ( Adjustment ) {
 int buff_lvl_step ;
 if ( cpi -> buffer_level < cpi -> oxcf . maximum_buffer_size ) {
 buff_lvl_step = ( int ) ( ( cpi -> oxcf . maximum_buffer_size - cpi -> oxcf . optimal_buffer_level ) / Adjustment ) ;
 if ( buff_lvl_step ) Adjustment = ( int ) ( ( cpi -> buffer_level - cpi -> oxcf . optimal_buffer_level ) / buff_lvl_step ) ;
 else Adjustment = 0 ;
 }
 cpi -> active_worst_quality -= Adjustment ;
 if ( cpi -> active_worst_quality < cpi -> active_best_quality ) cpi -> active_worst_quality = cpi -> active_best_quality ;
 }
 }
 if ( ( cpi -> pass == 2 ) || ( cpi -> ni_frames > 150 ) ) {
 vp8_clear_system_state ( ) ;
 Q = cpi -> active_worst_quality ;
 if ( cm -> frame_type == KEY_FRAME ) {
 if ( cpi -> pass == 2 ) {
 if ( cpi -> gfu_boost > 600 ) cpi -> active_best_quality = kf_low_motion_minq [ Q ] ;
 else cpi -> active_best_quality = kf_high_motion_minq [ Q ] ;
 if ( cpi -> this_key_frame_forced ) {
 if ( cpi -> active_best_quality > cpi -> avg_frame_qindex * 7 / 8 ) cpi -> active_best_quality = cpi -> avg_frame_qindex * 7 / 8 ;
 else if ( cpi -> active_best_quality < cpi -> avg_frame_qindex >> 2 ) cpi -> active_best_quality = cpi -> avg_frame_qindex >> 2 ;
 }
 }
 else cpi -> active_best_quality = kf_high_motion_minq [ Q ] ;
 }
 else if ( cpi -> oxcf . number_of_layers == 1 && ( cm -> refresh_golden_frame || cpi -> common . refresh_alt_ref_frame ) ) {
 if ( ( cpi -> frames_since_key > 1 ) && ( cpi -> avg_frame_qindex < cpi -> active_worst_quality ) ) {
 Q = cpi -> avg_frame_qindex ;
 }
 if ( ( cpi -> oxcf . end_usage == USAGE_CONSTRAINED_QUALITY ) && ( Q < cpi -> cq_target_quality ) ) {
 Q = cpi -> cq_target_quality ;
 }
 if ( cpi -> pass == 2 ) {
 if ( cpi -> gfu_boost > 1000 ) cpi -> active_best_quality = gf_low_motion_minq [ Q ] ;
 else if ( cpi -> gfu_boost < 400 ) cpi -> active_best_quality = gf_high_motion_minq [ Q ] ;
 else cpi -> active_best_quality = gf_mid_motion_minq [ Q ] ;
 if ( cpi -> oxcf . end_usage == USAGE_CONSTRAINED_QUALITY ) {
 cpi -> active_best_quality = cpi -> active_best_quality * 15 / 16 ;
 }
 }
 else cpi -> active_best_quality = gf_high_motion_minq [ Q ] ;
 }
 else {
 cpi -> active_best_quality = inter_minq [ Q ] ;
 if ( ( cpi -> oxcf . end_usage == USAGE_CONSTRAINED_QUALITY ) && ( cpi -> active_best_quality < cpi -> cq_target_quality ) ) {
 if ( cpi -> rolling_actual_bits < cpi -> min_frame_bandwidth ) cpi -> active_best_quality = cpi -> oxcf . cq_level ;
 else cpi -> active_best_quality = cpi -> cq_target_quality ;
 }
 }
 if ( cpi -> oxcf . end_usage == USAGE_STREAM_FROM_SERVER ) {
 if ( cpi -> buffer_level >= cpi -> oxcf . maximum_buffer_size ) cpi -> active_best_quality = cpi -> best_quality ;
 else if ( cpi -> buffer_level > cpi -> oxcf . optimal_buffer_level ) {
 int Fraction = ( int ) ( ( ( cpi -> buffer_level - cpi -> oxcf . optimal_buffer_level ) * 128 ) / ( cpi -> oxcf . maximum_buffer_size - cpi -> oxcf . optimal_buffer_level ) ) ;
 int min_qadjustment = ( ( cpi -> active_best_quality - cpi -> best_quality ) * Fraction ) / 128 ;
 cpi -> active_best_quality -= min_qadjustment ;
 }
 }
 }
 else if ( cpi -> oxcf . end_usage == USAGE_CONSTRAINED_QUALITY ) {
 if ( ( cm -> frame_type == KEY_FRAME ) || cm -> refresh_golden_frame || cpi -> common . refresh_alt_ref_frame ) {
 cpi -> active_best_quality = cpi -> best_quality ;
 }
 else if ( cpi -> active_best_quality < cpi -> cq_target_quality ) {
 cpi -> active_best_quality = cpi -> cq_target_quality ;
 }
 }
 if ( cpi -> active_worst_quality > cpi -> worst_quality ) cpi -> active_worst_quality = cpi -> worst_quality ;
 if ( cpi -> active_best_quality < cpi -> best_quality ) cpi -> active_best_quality = cpi -> best_quality ;
 if ( cpi -> active_worst_quality < cpi -> active_best_quality ) cpi -> active_worst_quality = cpi -> active_best_quality ;
 Q = vp8_regulate_q ( cpi , cpi -> this_frame_target ) ;

 else if ( ( cpi -> oxcf . number_of_layers == 1 ) && ( ( cm -> refresh_alt_ref_frame || ( cm -> refresh_golden_frame && ! cpi -> source_alt_ref_active ) ) ) ) {
 zbin_oq_high = 16 ;
 }
 else zbin_oq_high = ZBIN_OQ_MAX ;

 if ( cpi -> current_layer == 0 ) cyclic_background_refresh ( cpi , Q , 0 ) ;
 else disable_segmentation ( cpi ) ;
 }
 vp8_compute_frame_size_bounds ( cpi , & frame_under_shoot_limit , & frame_over_shoot_limit ) ;

 top_index = cpi -> active_worst_quality ;
 q_low = cpi -> active_best_quality ;
 q_high = cpi -> active_worst_quality ;

 loop_count = 0 ;
 scale_and_extend_source ( cpi -> un_scaled_source , cpi ) ;

 unsigned char * src ;
 int l = 0 ;
 switch ( cpi -> oxcf . noise_sensitivity ) {
 case 1 : l = 20 ;
 break ;
 case 2 : l = 40 ;
 break ;
 case 3 : l = 60 ;
 break ;
 case 4 : l = 80 ;
 break ;
 case 5 : l = 100 ;
 break ;
 case 6 : l = 150 ;
 break ;
 }
 if ( cm -> frame_type == KEY_FRAME ) {
 vp8_de_noise ( cm , cpi -> Source , cpi -> Source , l , 1 , 0 ) ;
 }
 else {
 vp8_de_noise ( cm , cpi -> Source , cpi -> Source , l , 1 , 0 ) ;
 src = cpi -> Source -> y_buffer ;
 if ( cpi -> Source -> y_stride < 0 ) {
 src += cpi -> Source -> y_stride * ( cpi -> Source -> y_height - 1 ) ;
 }
 }
 }


 vp8_clear_system_state ( ) ;
 vp8_set_quantizer ( cpi , Q ) ;
 if ( cpi -> common . mb_no_coeff_skip ) {
 cpi -> prob_skip_false = cpi -> base_skip_false_prob [ Q ] ;
 if ( cm -> frame_type != KEY_FRAME ) {
 if ( cpi -> common . refresh_alt_ref_frame ) {
 if ( cpi -> last_skip_false_probs [ 2 ] != 0 ) cpi -> prob_skip_false = cpi -> last_skip_false_probs [ 2 ] ;
 }
 else if ( cpi -> common . refresh_golden_frame ) {
 if ( cpi -> last_skip_false_probs [ 1 ] != 0 ) cpi -> prob_skip_false = cpi -> last_skip_false_probs [ 1 ] ;
 }
 else {
 if ( cpi -> last_skip_false_probs [ 0 ] != 0 ) cpi -> prob_skip_false = cpi -> last_skip_false_probs [ 0 ] ;
 }
 if ( cpi -> prob_skip_false < 5 ) cpi -> prob_skip_false = 5 ;
 if ( cpi -> prob_skip_false > 250 ) cpi -> prob_skip_false = 250 ;
 if ( cpi -> oxcf . number_of_layers == 1 && cpi -> is_src_frame_alt_ref ) cpi -> prob_skip_false = 1 ;
 }

 FILE * f = fopen ( "skip.stt" , "a" ) ;
 fprintf ( f , "%d, %d, %4d " , cpi -> common . refresh_golden_frame , cpi -> common . refresh_alt_ref_frame , cpi -> prob_skip_false ) ;
 fclose ( f ) ;
 }

 if ( cm -> frame_type == KEY_FRAME ) {
 if ( resize_key_frame ( cpi ) ) {
 Q = vp8_regulate_q ( cpi , cpi -> this_frame_target ) ;
 if ( cpi -> cyclic_refresh_mode_enabled ) {
 if ( cpi -> current_layer == 0 ) cyclic_background_refresh ( cpi , Q , 0 ) ;
 else disable_segmentation ( cpi ) ;
 }
 vpx_memset ( cpi -> consec_zero_last , 0 , cm -> mb_rows * cm -> mb_cols ) ;
 vp8_set_quantizer ( cpi , Q ) ;
 }
 vp8_setup_key_frame ( cpi ) ;
 }

 if ( cpi -> oxcf . error_resilient_mode ) cm -> refresh_entropy_probs = 0 ;
 if ( cpi -> oxcf . error_resilient_mode & VPX_ERROR_RESILIENT_PARTITIONS ) {
 if ( cm -> frame_type == KEY_FRAME ) cm -> refresh_entropy_probs = 1 ;
 }
 if ( cm -> refresh_entropy_probs == 0 ) {
 vpx_memcpy ( & cm -> lfc , & cm -> fc , sizeof ( cm -> fc ) ) ;
 }
 vp8_update_coef_context ( cpi ) ;
 vp8_update_coef_probs ( cpi ) ;
 vp8_encode_frame ( cpi ) ;
 }

 cpi -> projected_frame_size -= vp8_estimate_entropy_savings ( cpi ) ;
 cpi -> projected_frame_size = ( cpi -> projected_frame_size > 0 ) ? cpi -> projected_frame_size : 0 ;

 if ( cpi -> pass != 2 && cpi -> oxcf . auto_key && cm -> frame_type != KEY_FRAME && cpi -> compressor_speed != 2 ) {

 cm -> frame_type = KEY_FRAME ;
 vp8_pick_frame_size ( cpi ) ;
 cpi -> source_alt_ref_active = 0 ;
 setup_features ( cpi ) ;
 vp8_restore_coding_context ( cpi ) ;
 Q = vp8_regulate_q ( cpi , cpi -> this_frame_target ) ;
 vp8_compute_frame_size_bounds ( cpi , & frame_under_shoot_limit , & frame_over_shoot_limit ) ;
 bottom_index = cpi -> active_best_quality ;
 top_index = cpi -> active_worst_quality ;
 q_low = cpi -> active_best_quality ;
 q_high = cpi -> active_worst_quality ;
 loop_count ++ ;
 Loop = 1 ;
 continue ;
 }

 vp8_clear_system_state ( ) ;
 if ( frame_over_shoot_limit == 0 ) frame_over_shoot_limit = 1 ;
 if ( ( ( cpi -> pass != 2 ) || ( cpi -> oxcf . end_usage == USAGE_STREAM_FROM_SERVER ) ) && ( Q == cpi -> active_worst_quality ) && ( cpi -> active_worst_quality < cpi -> worst_quality ) && ( cpi -> projected_frame_size > frame_over_shoot_limit ) ) {
 int over_size_percent = ( ( cpi -> projected_frame_size - frame_over_shoot_limit ) * 100 ) / frame_over_shoot_limit ;
 while ( ( cpi -> active_worst_quality < cpi -> worst_quality ) && ( over_size_percent > 0 ) ) {
 cpi -> active_worst_quality ++ ;
 over_size_percent = ( int ) ( over_size_percent * 0.96 ) ;
 }


 }
 else active_worst_qchanged = 0 ;

 int last_q = Q ;
 int kf_err = vp8_calc_ss_err ( cpi -> Source , & cm -> yv12_fb [ cm -> new_fb_idx ] ) ;
 if ( kf_err > ( ( cpi -> ambient_err * 7 ) >> 3 ) ) {
 q_high = ( Q > q_low ) ? ( Q - 1 ) : q_low ;
 Q = ( q_high + q_low ) >> 1 ;
 }
 else if ( kf_err < ( cpi -> ambient_err >> 1 ) ) {
 q_low = ( Q < q_high ) ? ( Q + 1 ) : q_high ;
 Q = ( q_high + q_low + 1 ) >> 1 ;
 }
 if ( Q > q_high ) Q = q_high ;
 else if ( Q < q_low ) Q = q_low ;
 Loop = Q != last_q ;
 }
 else if ( recode_loop_test ( cpi , frame_over_shoot_limit , frame_under_shoot_limit , Q , top_index , bottom_index ) ) {
 int last_q = Q ;
 int Retries = 0 ;
 if ( cpi -> projected_frame_size > cpi -> this_frame_target ) {
 q_low = ( Q < q_high ) ? ( Q + 1 ) : q_high ;
 if ( cpi -> mb . zbin_over_quant > 0 ) zbin_oq_low = ( cpi -> mb . zbin_over_quant < zbin_oq_high ) ? ( cpi -> mb . zbin_over_quant + 1 ) : zbin_oq_high ;
 if ( undershoot_seen ) {
 if ( ! active_worst_qchanged ) vp8_update_rate_correction_factors ( cpi , 1 ) ;
 Q = ( q_high + q_low + 1 ) / 2 ;
 if ( Q < MAXQ ) cpi -> mb . zbin_over_quant = 0 ;
 else {
 zbin_oq_low = ( cpi -> mb . zbin_over_quant < zbin_oq_high ) ? ( cpi -> mb . zbin_over_quant + 1 ) : zbin_oq_high ;
 cpi -> mb . zbin_over_quant = ( zbin_oq_high + zbin_oq_low ) / 2 ;
 }
 }
 else {
 if ( ! active_worst_qchanged ) vp8_update_rate_correction_factors ( cpi , 0 ) ;
 Q = vp8_regulate_q ( cpi , cpi -> this_frame_target ) ;
 while ( ( ( Q < q_low ) || ( cpi -> mb . zbin_over_quant < zbin_oq_low ) ) && ( Retries < 10 ) ) {
 vp8_update_rate_correction_factors ( cpi , 0 ) ;
 Q = vp8_regulate_q ( cpi , cpi -> this_frame_target ) ;
 Retries ++ ;
 }
 }
 overshoot_seen = 1 ;
 }
 else {
 if ( cpi -> mb . zbin_over_quant == 0 ) q_high = ( Q > q_low ) ? ( Q - 1 ) : q_low ;
 else zbin_oq_high = ( cpi -> mb . zbin_over_quant > zbin_oq_low ) ? ( cpi -> mb . zbin_over_quant - 1 ) : zbin_oq_low ;
 if ( overshoot_seen ) {
 if ( ! active_worst_qchanged ) vp8_update_rate_correction_factors ( cpi , 1 ) ;
 Q = ( q_high + q_low ) / 2 ;
 if ( Q < MAXQ ) cpi -> mb . zbin_over_quant = 0 ;
 else cpi -> mb . zbin_over_quant = ( zbin_oq_high + zbin_oq_low ) / 2 ;
 }
 else {
 if ( ! active_worst_qchanged ) vp8_update_rate_correction_factors ( cpi , 0 ) ;
 Q = vp8_regulate_q ( cpi , cpi -> this_frame_target ) ;
 if ( ( cpi -> oxcf . end_usage == USAGE_CONSTRAINED_QUALITY ) && ( Q < q_low ) ) {
 q_low = Q ;
 }
 while ( ( ( Q > q_high ) || ( cpi -> mb . zbin_over_quant > zbin_oq_high ) ) && ( Retries < 10 ) ) {
 vp8_update_rate_correction_factors ( cpi , 0 ) ;
 Q = vp8_regulate_q ( cpi , cpi -> this_frame_target ) ;
 Retries ++ ;
 }
 }
 undershoot_seen = 1 ;
 }
 if ( Q > q_high ) Q = q_high ;
 else if ( Q < q_low ) Q = q_low ;
 cpi -> mb . zbin_over_quant = ( cpi -> mb . zbin_over_quant < zbin_oq_low ) ? zbin_oq_low : ( cpi -> mb . zbin_over_quant > zbin_oq_high ) ? zbin_oq_high : cpi -> mb . zbin_over_quant ;
 Loop = Q != last_q ;
 }
 else # endif Loop = 0 ;
 if ( cpi -> is_src_frame_alt_ref ) Loop = 0 ;
 if ( Loop == 1 ) {
 vp8_restore_coding_context ( cpi ) ;
 loop_count ++ ;


 }
 while ( Loop == 1 ) ;

 cpi -> one_pass_frame_stats [ cpi -> one_pass_frame_index ] . frame_coded_error = ( double ) cpi -> prediction_error ;
 cpi -> one_pass_frame_stats [ cpi -> one_pass_frame_index ] . frame_intra_error = ( double ) cpi -> intra_error ;
 cpi -> one_pass_frame_stats [ cpi -> one_pass_frame_index ] . frame_pcnt_inter = ( double ) ( 100 - cpi -> this_frame_percent_intra ) / 100.0 ;
 }

 cpi -> ambient_err = vp8_calc_ss_err ( cpi -> Source , & cm -> yv12_fb [ cm -> new_fb_idx ] ) ;
 }

 int mb_row ;
 int mb_col ;
 MODE_INFO * tmp = cm -> mip ;
 if ( cm -> frame_type != KEY_FRAME ) {
 for ( mb_row = 0 ;
 mb_row < cm -> mb_rows + 1 ;
 mb_row ++ ) {
 for ( mb_col = 0 ;
 mb_col < cm -> mb_cols + 1 ;
 mb_col ++ ) {
 if ( tmp -> mbmi . ref_frame != INTRA_FRAME ) cpi -> lfmv [ mb_col + mb_row * ( cm -> mode_info_stride + 1 ) ] . as_int = tmp -> mbmi . mv . as_int ;
 cpi -> lf_ref_frame_sign_bias [ mb_col + mb_row * ( cm -> mode_info_stride + 1 ) ] = cm -> ref_frame_sign_bias [ tmp -> mbmi . ref_frame ] ;
 cpi -> lf_ref_frame [ mb_col + mb_row * ( cm -> mode_info_stride + 1 ) ] = tmp -> mbmi . ref_frame ;
 tmp ++ ;
 }
 }
 }
 }
 {
 int mb_row ;
 int mb_col ;
 MODE_INFO * tmp = cm -> mi ;
 cpi -> zeromv_count = 0 ;
 if ( cm -> frame_type != KEY_FRAME ) {
 for ( mb_row = 0 ;
 mb_row < cm -> mb_rows ;
 mb_row ++ ) {
 for ( mb_col = 0 ;
 mb_col < cm -> mb_cols ;
 mb_col ++ ) {
 if ( tmp -> mbmi . mode == ZEROMV && tmp -> mbmi . ref_frame == LAST_FRAME ) cpi -> zeromv_count ++ ;
 tmp ++ ;
 }
 tmp ++ ;
 }
 }
 }


 if ( cm -> frame_type == KEY_FRAME ) cm -> refresh_last_frame = 1 ;

 FILE * f = fopen ( "gfactive.stt" , "a" ) ;
 fprintf ( f , "%8d %8d %8d %8d %8d\n" , cm -> current_video_frame , ( 100 * cpi -> gf_active_count ) / ( cpi -> common . mb_rows * cpi -> common . mb_cols ) , cpi -> this_iiratio , cpi -> next_iiratio , cm -> refresh_golden_frame ) ;
 fclose ( f ) ;
 }

 else cm -> copy_buffer_to_arf = 0 ;
 cm -> frame_to_show = & cm -> yv12_fb [ cm -> new_fb_idx ] ;

 process_denoiser_mode_change ( cpi ) ;
 }

 sem_post ( & cpi -> h_event_start_lpf ) ;
 cpi -> b_lpf_running = 1 ;
 }
 else # endif {
 vp8_loopfilter_frame ( cpi , cm ) ;
 }
 update_reference_frames ( cpi ) ;


 cm -> refresh_entropy_probs = 0 ;
 }



 sem_wait ( & cpi -> h_event_end_lpf ) ;
 cpi -> b_lpf_running = 0 ;
 }

 cpi -> total_byte_count += ( * size ) ;
 cpi -> projected_frame_size = ( * size ) << 3 ;
 if ( cpi -> oxcf . number_of_layers > 1 ) {
 unsigned int i ;
 for ( i = cpi -> current_layer + 1 ;
 i < cpi -> oxcf . number_of_layers ;
 i ++ ) cpi -> layer_context [ i ] . total_byte_count += ( * size ) ;
 }
 if ( ! active_worst_qchanged ) vp8_update_rate_correction_factors ( cpi , 2 ) ;
 cpi -> last_q [ cm -> frame_type ] = cm -> base_qindex ;
 if ( cm -> frame_type == KEY_FRAME ) {
 vp8_adjust_key_frame_context ( cpi ) ;
 }
 if ( cm -> frame_type != KEY_FRAME ) cpi -> avg_frame_qindex = ( 2 + 3 * cpi -> avg_frame_qindex + cm -> base_qindex ) >> 2 ;
 if ( ( cm -> frame_type != KEY_FRAME ) && ( ( cpi -> oxcf . number_of_layers > 1 ) || ( ! cm -> refresh_golden_frame && ! cm -> refresh_alt_ref_frame ) ) ) {
 cpi -> ni_frames ++ ;
 if ( cpi -> pass == 2 ) {
 cpi -> ni_tot_qi += Q ;
 cpi -> ni_av_qi = ( cpi -> ni_tot_qi / cpi -> ni_frames ) ;
 }
 else {
 if ( cpi -> ni_frames > 150 ) {
 cpi -> ni_tot_qi += Q ;
 cpi -> ni_av_qi = ( cpi -> ni_tot_qi / cpi -> ni_frames ) ;
 }
 else {
 cpi -> ni_tot_qi += Q ;
 cpi -> ni_av_qi = ( ( cpi -> ni_tot_qi / cpi -> ni_frames ) + cpi -> worst_quality + 1 ) / 2 ;
 }
 if ( Q > cpi -> ni_av_qi ) cpi -> ni_av_qi = Q - 1 ;
 }
 }
 if ( ! cm -> show_frame ) cpi -> bits_off_target -= cpi -> projected_frame_size ;
 else cpi -> bits_off_target += cpi -> av_per_frame_bandwidth - cpi -> projected_frame_size ;
 if ( cpi -> bits_off_target > cpi -> oxcf . maximum_buffer_size ) cpi -> bits_off_target = cpi -> oxcf . maximum_buffer_size ;
 cpi -> rolling_target_bits = ( ( cpi -> rolling_target_bits * 3 ) + cpi -> this_frame_target + 2 ) / 4 ;
 cpi -> rolling_actual_bits = ( ( cpi -> rolling_actual_bits * 3 ) + cpi -> projected_frame_size + 2 ) / 4 ;
 cpi -> long_rolling_target_bits = ( ( cpi -> long_rolling_target_bits * 31 ) + cpi -> this_frame_target + 16 ) / 32 ;
 cpi -> long_rolling_actual_bits = ( ( cpi -> long_rolling_actual_bits * 31 ) + cpi -> projected_frame_size + 16 ) / 32 ;
 cpi -> total_actual_bits += cpi -> projected_frame_size ;
 cpi -> total_target_vs_actual += ( cpi -> this_frame_target - cpi -> projected_frame_size ) ;
 cpi -> buffer_level = cpi -> bits_off_target ;
 if ( cpi -> oxcf . number_of_layers > 1 ) {
 unsigned int i ;
 for ( i = cpi -> current_layer + 1 ;
 i < cpi -> oxcf . number_of_layers ;
 i ++ ) {
 LAYER_CONTEXT * lc = & cpi -> layer_context [ i ] ;
 int bits_off_for_this_layer = ( int ) ( lc -> target_bandwidth / lc -> framerate - cpi -> projected_frame_size ) ;
 lc -> bits_off_target += bits_off_for_this_layer ;
 if ( lc -> bits_off_target > lc -> maximum_buffer_size ) lc -> bits_off_target = lc -> maximum_buffer_size ;
 lc -> total_actual_bits += cpi -> projected_frame_size ;
 lc -> total_target_vs_actual += bits_off_for_this_layer ;
 lc -> buffer_level = lc -> bits_off_target ;
 }
 }
 if ( cm -> frame_type == KEY_FRAME ) {
 cpi -> twopass . kf_group_bits += cpi -> this_frame_target - cpi -> projected_frame_size ;
 if ( cpi -> twopass . kf_group_bits < 0 ) cpi -> twopass . kf_group_bits = 0 ;
 }
 else if ( cm -> refresh_golden_frame || cm -> refresh_alt_ref_frame ) {
 cpi -> twopass . gf_group_bits += cpi -> this_frame_target - cpi -> projected_frame_size ;
 if ( cpi -> twopass . gf_group_bits < 0 ) cpi -> twopass . gf_group_bits = 0 ;
 }
 if ( cm -> frame_type != KEY_FRAME ) {
 if ( cpi -> common . refresh_alt_ref_frame ) {
 cpi -> last_skip_false_probs [ 2 ] = cpi -> prob_skip_false ;
 cpi -> last_skip_probs_q [ 2 ] = cm -> base_qindex ;
 }
 else if ( cpi -> common . refresh_golden_frame ) {
 cpi -> last_skip_false_probs [ 1 ] = cpi -> prob_skip_false ;
 cpi -> last_skip_probs_q [ 1 ] = cm -> base_qindex ;
 }
 else {
 cpi -> last_skip_false_probs [ 0 ] = cpi -> prob_skip_false ;
 cpi -> last_skip_probs_q [ 0 ] = cm -> base_qindex ;
 cpi -> base_skip_false_prob [ cm -> base_qindex ] = cpi -> prob_skip_false ;
 }
 }

 FILE * f = fopen ( "tmp.stt" , "a" ) ;
 vp8_clear_system_state ( ) ;
 if ( cpi -> twopass . total_left_stats . coded_error != 0.0 ) fprintf ( f , "%10d %10d %10d %10d %10d %10" PRId64 " %10" PRId64 "%10" PRId64 " %10d %6d %6d %6d %6d %5d %5d %5d %8d " "%8.2lf %" PRId64 " %10.3lf %10" PRId64 " %8d\n" , cpi -> common . current_video_frame , cpi -> this_frame_target , cpi -> projected_frame_size , ( cpi -> projected_frame_size - cpi -> this_frame_target ) , cpi -> total_target_vs_actual , cpi -> buffer_level , ( cpi -> oxcf . starting_buffer_level - cpi -> bits_off_target ) , cpi -> total_actual_bits , cm -> base_qindex , cpi -> active_best_quality , cpi -> active_worst_quality , cpi -> ni_av_qi , cpi -> cq_target_quality , cm -> refresh_golden_frame , cm -> refresh_alt_ref_frame , cm -> frame_type , cpi -> gfu_boost , cpi -> twopass . est_max_qcorrection_factor , cpi -> twopass . bits_left , cpi -> twopass . total_left_stats . coded_error , ( double ) cpi -> twopass . bits_left / cpi -> twopass . total_left_stats . coded_error , cpi -> tot_recode_hits ) ;
 else fprintf ( f , "%10d %10d %10d %10d %10d %10" PRId64 " %10" PRId64 "%10" PRId64 " %10d %6d %6d %6d %6d %5d %5d %5d %8d " "%8.2lf %" PRId64 " %10.3lf %8d\n" , cpi -> common . current_video_frame , cpi -> this_frame_target , cpi -> projected_frame_size , ( cpi -> projected_frame_size - cpi -> this_frame_target ) , cpi -> total_target_vs_actual , cpi -> buffer_level , ( cpi -> oxcf . starting_buffer_level - cpi -> bits_off_target ) , cpi -> total_actual_bits , cm -> base_qindex , cpi -> active_best_quality , cpi -> active_worst_quality , cpi -> ni_av_qi , cpi -> cq_target_quality , cm -> refresh_golden_frame , cm -> refresh_alt_ref_frame , cm -> frame_type , cpi -> gfu_boost , cpi -> twopass . est_max_qcorrection_factor , cpi -> twopass . bits_left , cpi -> twopass . total_left_stats . coded_error , cpi -> tot_recode_hits ) ;
 fclose ( f ) ;
 {
 FILE * fmodes = fopen ( "Modes.stt" , "a" ) ;
 fprintf ( fmodes , "%6d:%1d:%1d:%1d " , cpi -> common . current_video_frame , cm -> frame_type , cm -> refresh_golden_frame , cm -> refresh_alt_ref_frame ) ;
 fprintf ( fmodes , "\n" ) ;
 fclose ( fmodes ) ;
 }
 }

 else cm -> frame_flags = cm -> frame_flags & ~ FRAMEFLAGS_GOLDEN ;
 if ( cm -> refresh_alt_ref_frame == 1 ) cm -> frame_flags = cm -> frame_flags | FRAMEFLAGS_ALTREF ;
 else cm -> frame_flags = cm -> frame_flags & ~ FRAMEFLAGS_ALTREF ;
 if ( cm -> refresh_last_frame & cm -> refresh_golden_frame ) cpi -> gold_is_last = 1 ;
 else if ( cm -> refresh_last_frame ^ cm -> refresh_golden_frame ) cpi -> gold_is_last = 0 ;
 if ( cm -> refresh_last_frame & cm -> refresh_alt_ref_frame ) cpi -> alt_is_last = 1 ;
 else if ( cm -> refresh_last_frame ^ cm -> refresh_alt_ref_frame ) cpi -> alt_is_last = 0 ;
 if ( cm -> refresh_alt_ref_frame & cm -> refresh_golden_frame ) cpi -> gold_is_alt = 1 ;
 else if ( cm -> refresh_alt_ref_frame ^ cm -> refresh_golden_frame ) cpi -> gold_is_alt = 0 ;
 cpi -> ref_frame_flags = VP8_ALTR_FRAME | VP8_GOLD_FRAME | VP8_LAST_FRAME ;
 if ( cpi -> gold_is_last ) cpi -> ref_frame_flags &= ~ VP8_GOLD_FRAME ;
 if ( cpi -> alt_is_last ) cpi -> ref_frame_flags &= ~ VP8_ALTR_FRAME ;
 if ( cpi -> gold_is_alt ) cpi -> ref_frame_flags &= ~ VP8_ALTR_FRAME ;
 if ( ! cpi -> oxcf . error_resilient_mode ) {
 if ( cpi -> oxcf . play_alternate && cm -> refresh_alt_ref_frame && ( cm -> frame_type != KEY_FRAME ) ) update_alt_ref_frame_stats ( cpi ) ;
 else update_golden_frame_stats ( cpi ) ;
 }
 if ( cm -> frame_type == KEY_FRAME ) {
 * frame_flags = cm -> frame_flags | FRAMEFLAGS_KEY ;
 cm -> frame_type = INTER_FRAME ;
 cpi -> last_frame_percent_intra = 100 ;
 }
 else {
 * frame_flags = cm -> frame_flags & ~ FRAMEFLAGS_KEY ;
 cpi -> last_frame_percent_intra = cpi -> this_frame_percent_intra ;
 }
 cpi -> mb . e_mbd . update_mb_segmentation_map = 0 ;
 cpi -> mb . e_mbd . update_mb_segmentation_data = 0 ;
 cpi -> mb . e_mbd . mode_ref_lf_delta_update = 0 ;
 if ( cm -> show_frame ) {
 cm -> current_video_frame ++ ;
 cpi -> frames_since_key ++ ;
 cpi -> temporal_pattern_counter ++ ;
 }

 char filename [ 512 ] ;
 FILE * recon_file ;
 sprintf ( filename , "enc%04d.yuv" , ( int ) cm -> current_video_frame ) ;
 recon_file = fopen ( filename , "wb" ) ;
 fwrite ( cm -> yv12_fb [ cm -> lst_fb_idx ] . buffer_alloc , cm -> yv12_fb [ cm -> lst_fb_idx ] . frame_size , 1 , recon_file ) ;
 fclose ( recon_file ) ;
 }

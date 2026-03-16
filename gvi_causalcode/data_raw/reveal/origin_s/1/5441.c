static void set_good_speed_feature ( VP9_COMP * cpi , VP9_COMMON * cm , SPEED_FEATURES * sf , int speed ) {
 const int boosted = frame_is_boosted ( cpi ) ;
 sf -> adaptive_rd_thresh = 1 ;
 sf -> allow_skip_recode = 1 ;
 if ( speed >= 1 ) {
 sf -> use_square_partition_only = ! frame_is_intra_only ( cm ) ;
 sf -> less_rectangular_check = 1 ;
 if ( MIN ( cm -> width , cm -> height ) >= 720 ) sf -> disable_split_mask = cm -> show_frame ? DISABLE_ALL_SPLIT : DISABLE_ALL_INTER_SPLIT ;
 else sf -> disable_split_mask = DISABLE_COMPOUND_SPLIT ;
 sf -> use_rd_breakout = 1 ;
 sf -> adaptive_motion_search = 1 ;
 sf -> mv . auto_mv_step_size = 1 ;
 sf -> adaptive_rd_thresh = 2 ;
 sf -> mv . subpel_iters_per_step = 1 ;
 sf -> mode_skip_start = 10 ;
 sf -> adaptive_pred_interp_filter = 1 ;
 sf -> recode_loop = ALLOW_RECODE_KFARFGF ;
 sf -> intra_y_mode_mask [ TX_32X32 ] = INTRA_DC_H_V ;
 sf -> intra_uv_mode_mask [ TX_32X32 ] = INTRA_DC_H_V ;
 sf -> intra_y_mode_mask [ TX_16X16 ] = INTRA_DC_H_V ;
 sf -> intra_uv_mode_mask [ TX_16X16 ] = INTRA_DC_H_V ;
 sf -> tx_size_search_breakout = 1 ;
 if ( MIN ( cm -> width , cm -> height ) >= 720 ) sf -> partition_search_breakout_dist_thr = ( 1 << 23 ) ;
 else sf -> partition_search_breakout_dist_thr = ( 1 << 21 ) ;
 sf -> partition_search_breakout_rate_thr = 500 ;
 }
 if ( speed >= 2 ) {
 sf -> tx_size_search_method = frame_is_boosted ( cpi ) ? USE_FULL_RD : USE_LARGESTALL ;
 if ( MIN ( cm -> width , cm -> height ) >= 720 ) {
 sf -> lf_motion_threshold = LOW_MOTION_THRESHOLD ;
 sf -> last_partitioning_redo_frequency = 3 ;
 sf -> disable_split_mask = cm -> show_frame ? DISABLE_ALL_SPLIT : DISABLE_ALL_INTER_SPLIT ;
 sf -> adaptive_pred_interp_filter = 0 ;
 }
 else {
 sf -> disable_split_mask = LAST_AND_INTRA_SPLIT_ONLY ;
 sf -> last_partitioning_redo_frequency = 2 ;
 sf -> lf_motion_threshold = NO_MOTION_THRESHOLD ;
 }
 sf -> reference_masking = 1 ;
 sf -> mode_search_skip_flags = FLAG_SKIP_INTRA_DIRMISMATCH | FLAG_SKIP_INTRA_BESTINTER | FLAG_SKIP_COMP_BESTINTRA | FLAG_SKIP_INTRA_LOWVAR ;
 sf -> disable_filter_search_var_thresh = 100 ;
 sf -> comp_inter_joint_search_thresh = BLOCK_SIZES ;
 sf -> auto_min_max_partition_size = CONSTRAIN_NEIGHBORING_MIN_MAX ;
 sf -> use_lastframe_partitioning = LAST_FRAME_PARTITION_LOW_MOTION ;
 sf -> adjust_partitioning_from_last_frame = 1 ;
 if ( MIN ( cm -> width , cm -> height ) >= 720 ) sf -> partition_search_breakout_dist_thr = ( 1 << 24 ) ;
 else sf -> partition_search_breakout_dist_thr = ( 1 << 22 ) ;
 sf -> partition_search_breakout_rate_thr = 700 ;
 }
 if ( speed >= 3 ) {
 sf -> tx_size_search_method = frame_is_intra_only ( cm ) ? USE_FULL_RD : USE_LARGESTALL ;
 if ( MIN ( cm -> width , cm -> height ) >= 720 ) {
 sf -> disable_split_mask = DISABLE_ALL_SPLIT ;
 }
 else {
 sf -> max_intra_bsize = BLOCK_32X32 ;
 sf -> disable_split_mask = DISABLE_ALL_INTER_SPLIT ;
 }
 sf -> adaptive_pred_interp_filter = 0 ;
 sf -> adaptive_mode_search = 1 ;
 sf -> cb_partition_search = ! boosted ;
 sf -> cb_pred_filter_search = 1 ;
 sf -> alt_ref_search_fp = 1 ;
 sf -> motion_field_mode_search = ! boosted ;
 sf -> lf_motion_threshold = LOW_MOTION_THRESHOLD ;
 sf -> last_partitioning_redo_frequency = 2 ;
 sf -> recode_loop = ALLOW_RECODE_KFMAXBW ;
 sf -> adaptive_rd_thresh = 3 ;
 sf -> mode_skip_start = 6 ;
 sf -> intra_y_mode_mask [ TX_32X32 ] = INTRA_DC ;
 sf -> intra_uv_mode_mask [ TX_32X32 ] = INTRA_DC ;
 sf -> adaptive_interp_filter_search = 1 ;
 if ( MIN ( cm -> width , cm -> height ) >= 720 ) sf -> partition_search_breakout_dist_thr = ( 1 << 25 ) ;
 else sf -> partition_search_breakout_dist_thr = ( 1 << 23 ) ;
 sf -> partition_search_breakout_rate_thr = 1000 ;
 }
 if ( speed >= 4 ) {
 sf -> use_square_partition_only = 1 ;
 sf -> tx_size_search_method = USE_LARGESTALL ;
 sf -> disable_split_mask = DISABLE_ALL_SPLIT ;
 sf -> adaptive_rd_thresh = 4 ;
 sf -> mode_search_skip_flags |= FLAG_SKIP_COMP_REFMISMATCH | FLAG_EARLY_TERMINATE ;
 sf -> disable_filter_search_var_thresh = 200 ;
 sf -> use_lastframe_partitioning = LAST_FRAME_PARTITION_ALL ;
 sf -> use_lp32x32fdct = 1 ;
 sf -> use_fast_coef_updates = ONE_LOOP_REDUCED ;
 sf -> use_fast_coef_costing = 1 ;
 if ( MIN ( cm -> width , cm -> height ) >= 720 ) sf -> partition_search_breakout_dist_thr = ( 1 << 26 ) ;
 else sf -> partition_search_breakout_dist_thr = ( 1 << 24 ) ;
 sf -> partition_search_breakout_rate_thr = 1500 ;
 }
 if ( speed >= 5 ) {
 int i ;
 sf -> partition_search_type = FIXED_PARTITION ;
 sf -> optimize_coefficients = 0 ;
 sf -> mv . search_method = HEX ;
 sf -> disable_filter_search_var_thresh = 500 ;
 for ( i = 0 ;
 i < TX_SIZES ;
 ++ i ) {
 sf -> intra_y_mode_mask [ i ] = INTRA_DC ;
 sf -> intra_uv_mode_mask [ i ] = INTRA_DC ;
 }
 cpi -> allow_encode_breakout = ENCODE_BREAKOUT_ENABLED ;
 }
 if ( speed >= 6 ) {
 sf -> mv . reduce_first_step_size = 1 ;
 }
 }
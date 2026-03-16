static void set_rt_speed_feature ( VP9_COMP * cpi , SPEED_FEATURES * sf , int speed , vp9e_tune_content content ) {
 VP9_COMMON * const cm = & cpi -> common ;
 const int is_keyframe = cm -> frame_type == KEY_FRAME ;
 const int frames_since_key = is_keyframe ? 0 : cpi -> rc . frames_since_key ;
 sf -> static_segmentation = 0 ;
 sf -> adaptive_rd_thresh = 1 ;
 sf -> use_fast_coef_costing = 1 ;
 if ( speed >= 1 ) {
 sf -> use_square_partition_only = ! frame_is_intra_only ( cm ) ;
 sf -> less_rectangular_check = 1 ;
 sf -> tx_size_search_method = frame_is_intra_only ( cm ) ? USE_FULL_RD : USE_LARGESTALL ;
 if ( MIN ( cm -> width , cm -> height ) >= 720 ) sf -> disable_split_mask = cm -> show_frame ? DISABLE_ALL_SPLIT : DISABLE_ALL_INTER_SPLIT ;
 else sf -> disable_split_mask = DISABLE_COMPOUND_SPLIT ;
 sf -> use_rd_breakout = 1 ;
 sf -> adaptive_motion_search = 1 ;
 sf -> adaptive_pred_interp_filter = 1 ;
 sf -> mv . auto_mv_step_size = 1 ;
 sf -> adaptive_rd_thresh = 2 ;
 sf -> intra_y_mode_mask [ TX_32X32 ] = INTRA_DC_H_V ;
 sf -> intra_uv_mode_mask [ TX_32X32 ] = INTRA_DC_H_V ;
 sf -> intra_uv_mode_mask [ TX_16X16 ] = INTRA_DC_H_V ;
 }
 if ( speed >= 2 ) {
 if ( MIN ( cm -> width , cm -> height ) >= 720 ) sf -> disable_split_mask = cm -> show_frame ? DISABLE_ALL_SPLIT : DISABLE_ALL_INTER_SPLIT ;
 else sf -> disable_split_mask = LAST_AND_INTRA_SPLIT_ONLY ;
 sf -> mode_search_skip_flags = FLAG_SKIP_INTRA_DIRMISMATCH | FLAG_SKIP_INTRA_BESTINTER | FLAG_SKIP_COMP_BESTINTRA | FLAG_SKIP_INTRA_LOWVAR ;
 sf -> adaptive_pred_interp_filter = 2 ;
 sf -> reference_masking = 1 ;
 sf -> disable_filter_search_var_thresh = 50 ;
 sf -> comp_inter_joint_search_thresh = BLOCK_SIZES ;
 sf -> auto_min_max_partition_size = RELAXED_NEIGHBORING_MIN_MAX ;
 sf -> use_lastframe_partitioning = LAST_FRAME_PARTITION_LOW_MOTION ;
 sf -> lf_motion_threshold = LOW_MOTION_THRESHOLD ;
 sf -> adjust_partitioning_from_last_frame = 1 ;
 sf -> last_partitioning_redo_frequency = 3 ;
 sf -> use_lp32x32fdct = 1 ;
 sf -> mode_skip_start = 11 ;
 sf -> intra_y_mode_mask [ TX_16X16 ] = INTRA_DC_H_V ;
 }
 if ( speed >= 3 ) {
 sf -> use_square_partition_only = 1 ;
 sf -> disable_filter_search_var_thresh = 100 ;
 sf -> use_lastframe_partitioning = LAST_FRAME_PARTITION_ALL ;
 sf -> constrain_copy_partition = 1 ;
 sf -> use_uv_intra_rd_estimate = 1 ;
 sf -> skip_encode_sb = 1 ;
 sf -> mv . subpel_iters_per_step = 1 ;
 sf -> use_fast_coef_updates = ONE_LOOP_REDUCED ;
 sf -> adaptive_rd_thresh = 4 ;
 sf -> mode_skip_start = 6 ;
 sf -> allow_skip_recode = 0 ;
 sf -> optimize_coefficients = 0 ;
 sf -> disable_split_mask = DISABLE_ALL_SPLIT ;
 sf -> lpf_pick = LPF_PICK_FROM_Q ;
 }
 if ( speed >= 4 ) {
 int i ;
 sf -> last_partitioning_redo_frequency = 4 ;
 sf -> adaptive_rd_thresh = 5 ;
 sf -> use_fast_coef_costing = 0 ;
 sf -> auto_min_max_partition_size = STRICT_NEIGHBORING_MIN_MAX ;
 sf -> adjust_partitioning_from_last_frame = cm -> last_frame_type != cm -> frame_type || ( 0 == ( frames_since_key + 1 ) % sf -> last_partitioning_redo_frequency ) ;
 sf -> mv . subpel_force_stop = 1 ;
 for ( i = 0 ;
 i < TX_SIZES ;
 i ++ ) {
 sf -> intra_y_mode_mask [ i ] = INTRA_DC_H_V ;
 sf -> intra_uv_mode_mask [ i ] = INTRA_DC ;
 }
 sf -> intra_y_mode_mask [ TX_32X32 ] = INTRA_DC ;
 sf -> frame_parameter_update = 0 ;
 sf -> mv . search_method = FAST_HEX ;
 sf -> inter_mode_mask [ BLOCK_32X32 ] = INTER_NEAREST_NEAR_NEW ;
 sf -> inter_mode_mask [ BLOCK_32X64 ] = INTER_NEAREST ;
 sf -> inter_mode_mask [ BLOCK_64X32 ] = INTER_NEAREST ;
 sf -> inter_mode_mask [ BLOCK_64X64 ] = INTER_NEAREST ;
 sf -> max_intra_bsize = BLOCK_32X32 ;
 sf -> allow_skip_recode = 1 ;
 }
 if ( speed >= 5 ) {
 sf -> use_quant_fp = ! is_keyframe ;
 sf -> auto_min_max_partition_size = is_keyframe ? RELAXED_NEIGHBORING_MIN_MAX : STRICT_NEIGHBORING_MIN_MAX ;
 sf -> max_partition_size = BLOCK_32X32 ;
 sf -> min_partition_size = BLOCK_8X8 ;
 sf -> partition_check = ( frames_since_key % sf -> last_partitioning_redo_frequency == 1 ) ;
 sf -> force_frame_boost = is_keyframe || ( frames_since_key % ( sf -> last_partitioning_redo_frequency << 1 ) == 1 ) ;
 sf -> max_delta_qindex = is_keyframe ? 20 : 15 ;
 sf -> partition_search_type = REFERENCE_PARTITION ;
 sf -> use_nonrd_pick_mode = 1 ;
 sf -> allow_skip_recode = 0 ;
 }
 if ( speed >= 6 ) {
 if ( content == VP9E_CONTENT_SCREEN ) {
 int i ;
 for ( i = 0 ;
 i < BLOCK_SIZES ;
 ++ i ) sf -> inter_mode_mask [ i ] = INTER_ALL ;
 }
 sf -> partition_search_type = SOURCE_VAR_BASED_PARTITION ;
 sf -> search_type_check_frequency = 50 ;
 sf -> tx_size_search_method = is_keyframe ? USE_LARGESTALL : USE_TX_8X8 ;
 sf -> reuse_inter_pred_sby = 1 ;
 sf -> elevate_newmv_thresh = 2000 ;
 sf -> mv . reduce_first_step_size = 1 ;
 }
 if ( speed >= 7 ) {
 sf -> mv . search_method = FAST_DIAMOND ;
 sf -> mv . fullpel_search_step_param = 10 ;
 sf -> lpf_pick = LPF_PICK_MINIMAL_LPF ;
 sf -> encode_breakout_thresh = ( MIN ( cm -> width , cm -> height ) >= 720 ) ? : 300 ;
 sf -> elevate_newmv_thresh = 2500 ;
 }
 if ( speed >= 12 ) {
 sf -> elevate_newmv_thresh = 4000 ;
 sf -> mv . subpel_force_stop = 2 ;
 }
 if ( speed >= 13 ) {
 int i ;
 sf -> max_intra_bsize = BLOCK_32X32 ;
 for ( i = 0 ;
 i < BLOCK_SIZES ;
 ++ i ) sf -> inter_mode_mask [ i ] = INTER_NEAREST ;
 }
 }
static vpx_codec_err_t set_encoder_config ( VP9EncoderConfig * oxcf , const vpx_codec_enc_cfg_t * cfg , const struct vp9_extracfg * extra_cfg ) {
 const int is_vbr = cfg -> rc_end_usage == VPX_VBR ;
 oxcf -> profile = cfg -> g_profile ;
 oxcf -> width = cfg -> g_w ;
 oxcf -> height = cfg -> g_h ;
 oxcf -> bit_depth = extra_cfg -> bit_depth ;
 oxcf -> input_bit_depth = cfg -> g_input_bit_depth ;
 oxcf -> init_framerate = ( double ) cfg -> g_timebase . den / cfg -> g_timebase . num ;
 if ( oxcf -> init_framerate > 180 ) oxcf -> init_framerate = 30 ;
 oxcf -> mode = GOOD ;
 switch ( cfg -> g_pass ) {
 case VPX_RC_ONE_PASS : oxcf -> pass = 0 ;
 break ;
 case VPX_RC_FIRST_PASS : oxcf -> pass = 1 ;
 break ;
 case VPX_RC_LAST_PASS : oxcf -> pass = 2 ;
 break ;
 }
 oxcf -> lag_in_frames = cfg -> g_pass == VPX_RC_FIRST_PASS ? 0 : cfg -> g_lag_in_frames ;
 oxcf -> rc_mode = cfg -> rc_end_usage ;
 oxcf -> target_bandwidth = 1000 * cfg -> rc_target_bitrate ;
 oxcf -> rc_max_intra_bitrate_pct = extra_cfg -> rc_max_intra_bitrate_pct ;
 oxcf -> best_allowed_q = extra_cfg -> lossless ? 0 : vp9_quantizer_to_qindex ( cfg -> rc_min_quantizer ) ;
 oxcf -> worst_allowed_q = extra_cfg -> lossless ? 0 : vp9_quantizer_to_qindex ( cfg -> rc_max_quantizer ) ;
 oxcf -> cq_level = vp9_quantizer_to_qindex ( extra_cfg -> cq_level ) ;
 oxcf -> fixed_q = - 1 ;
 oxcf -> under_shoot_pct = cfg -> rc_undershoot_pct ;
 oxcf -> over_shoot_pct = cfg -> rc_overshoot_pct ;
 oxcf -> allow_spatial_resampling = cfg -> rc_resize_allowed ;
 oxcf -> scaled_frame_width = cfg -> rc_scaled_width ;
 oxcf -> scaled_frame_height = cfg -> rc_scaled_height ;
 oxcf -> maximum_buffer_size_ms = is_vbr ? 240000 : cfg -> rc_buf_sz ;
 oxcf -> starting_buffer_level_ms = is_vbr ? 60000 : cfg -> rc_buf_initial_sz ;
 oxcf -> optimal_buffer_level_ms = is_vbr ? 60000 : cfg -> rc_buf_optimal_sz ;
 oxcf -> drop_frames_water_mark = cfg -> rc_dropframe_thresh ;
 oxcf -> two_pass_vbrbias = cfg -> rc_2pass_vbr_bias_pct ;
 oxcf -> two_pass_vbrmin_section = cfg -> rc_2pass_vbr_minsection_pct ;
 oxcf -> two_pass_vbrmax_section = cfg -> rc_2pass_vbr_maxsection_pct ;
 oxcf -> auto_key = cfg -> kf_mode == VPX_KF_AUTO && cfg -> kf_min_dist != cfg -> kf_max_dist ;
 oxcf -> key_freq = cfg -> kf_max_dist ;
 oxcf -> speed = abs ( extra_cfg -> cpu_used ) ;
 oxcf -> encode_breakout = extra_cfg -> static_thresh ;
 oxcf -> play_alternate = extra_cfg -> enable_auto_alt_ref ;
 oxcf -> noise_sensitivity = extra_cfg -> noise_sensitivity ;
 oxcf -> sharpness = extra_cfg -> sharpness ;
 oxcf -> two_pass_stats_in = cfg -> rc_twopass_stats_in ;


 oxcf -> arnr_strength = extra_cfg -> arnr_strength ;
 oxcf -> tuning = extra_cfg -> tuning ;
 oxcf -> content = extra_cfg -> content ;
 oxcf -> tile_columns = extra_cfg -> tile_columns ;
 oxcf -> tile_rows = extra_cfg -> tile_rows ;
 oxcf -> error_resilient_mode = cfg -> g_error_resilient ;
 oxcf -> frame_parallel_decoding_mode = extra_cfg -> frame_parallel_decoding_mode ;
 oxcf -> aq_mode = extra_cfg -> aq_mode ;
 oxcf -> frame_periodic_boost = extra_cfg -> frame_periodic_boost ;
 oxcf -> ss_number_layers = cfg -> ss_number_layers ;
 if ( oxcf -> ss_number_layers > 1 ) {
 int i ;
 for ( i = 0 ;
 i < VPX_SS_MAX_LAYERS ;
 ++ i ) {
 oxcf -> ss_target_bitrate [ i ] = 1000 * cfg -> ss_target_bitrate [ i ] ;


 }
 else if ( oxcf -> ss_number_layers == 1 ) {
 oxcf -> ss_target_bitrate [ 0 ] = ( int ) oxcf -> target_bandwidth ;


 oxcf -> ts_number_layers = cfg -> ts_number_layers ;
 if ( oxcf -> ts_number_layers > 1 ) {
 int i ;
 for ( i = 0 ;
 i < VPX_TS_MAX_LAYERS ;
 ++ i ) {
 oxcf -> ts_target_bitrate [ i ] = 1000 * cfg -> ts_target_bitrate [ i ] ;
 oxcf -> ts_rate_decimator [ i ] = cfg -> ts_rate_decimator [ i ] ;
 }
 }
 else if ( oxcf -> ts_number_layers == 1 ) {
 oxcf -> ts_target_bitrate [ 0 ] = ( int ) oxcf -> target_bandwidth ;
 oxcf -> ts_rate_decimator [ 0 ] = 1 ;
 }
 return VPX_CODEC_OK ;
 }
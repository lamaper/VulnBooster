static vpx_codec_err_t validate_config ( vpx_codec_alg_priv_t * ctx , const vpx_codec_enc_cfg_t * cfg , const struct vp9_extracfg * extra_cfg ) {
 RANGE_CHECK ( cfg , g_w , 1 , 65535 ) ;
 RANGE_CHECK ( cfg , g_h , 1 , 65535 ) ;
 RANGE_CHECK ( cfg , g_timebase . den , 1 , 1000000000 ) ;
 RANGE_CHECK ( cfg , g_timebase . num , 1 , cfg -> g_timebase . den ) ;
 RANGE_CHECK_HI ( cfg , g_profile , 3 ) ;
 RANGE_CHECK_HI ( cfg , rc_max_quantizer , 63 ) ;
 RANGE_CHECK_HI ( cfg , rc_min_quantizer , cfg -> rc_max_quantizer ) ;
 RANGE_CHECK_BOOL ( extra_cfg , lossless ) ;
 RANGE_CHECK ( extra_cfg , aq_mode , 0 , AQ_MODE_COUNT - 1 ) ;
 RANGE_CHECK ( extra_cfg , frame_periodic_boost , 0 , 1 ) ;
 RANGE_CHECK_HI ( cfg , g_threads , 64 ) ;
 RANGE_CHECK_HI ( cfg , g_lag_in_frames , MAX_LAG_BUFFERS ) ;
 RANGE_CHECK ( cfg , rc_end_usage , VPX_VBR , VPX_Q ) ;
 RANGE_CHECK_HI ( cfg , rc_undershoot_pct , 1000 ) ;
 RANGE_CHECK_HI ( cfg , rc_overshoot_pct , 1000 ) ;
 RANGE_CHECK_HI ( cfg , rc_2pass_vbr_bias_pct , 100 ) ;
 RANGE_CHECK ( cfg , kf_mode , VPX_KF_DISABLED , VPX_KF_AUTO ) ;
 RANGE_CHECK_BOOL ( cfg , rc_resize_allowed ) ;
 RANGE_CHECK_HI ( cfg , rc_dropframe_thresh , 100 ) ;
 RANGE_CHECK_HI ( cfg , rc_resize_up_thresh , 100 ) ;
 RANGE_CHECK_HI ( cfg , rc_resize_down_thresh , 100 ) ;
 RANGE_CHECK ( cfg , g_pass , VPX_RC_ONE_PASS , VPX_RC_LAST_PASS ) ;
 if ( cfg -> rc_resize_allowed == 1 ) {
 RANGE_CHECK ( cfg , rc_scaled_width , 1 , cfg -> g_w ) ;
 RANGE_CHECK ( cfg , rc_scaled_height , 1 , cfg -> g_h ) ;
 }
 RANGE_CHECK ( cfg , ss_number_layers , 1 , VPX_SS_MAX_LAYERS ) ;
 RANGE_CHECK ( cfg , ts_number_layers , 1 , VPX_TS_MAX_LAYERS ) ;
 if ( cfg -> ts_number_layers > 1 ) {
 unsigned int i ;
 for ( i = 1 ;
 i < cfg -> ts_number_layers ;
 ++ i ) if ( cfg -> ts_target_bitrate [ i ] < cfg -> ts_target_bitrate [ i - 1 ] ) ERROR ( "ts_target_bitrate entries are not increasing" ) ;
 RANGE_CHECK ( cfg , ts_rate_decimator [ cfg -> ts_number_layers - 1 ] , 1 , 1 ) ;
 for ( i = cfg -> ts_number_layers - 2 ;
 i > 0 ;
 -- i ) if ( cfg -> ts_rate_decimator [ i - 1 ] != 2 * cfg -> ts_rate_decimator [ i ] ) ERROR ( "ts_rate_decimator factors are not powers of 2" ) ;
 }

 if ( ( cfg -> ss_number_layers > 1 || cfg -> ts_number_layers > 1 ) && cfg -> g_pass == VPX_RC_LAST_PASS ) {
 unsigned int i , alt_ref_sum = 0 ;
 for ( i = 0 ;
 i < cfg -> ss_number_layers ;
 ++ i ) {
 if ( cfg -> ss_enable_auto_alt_ref [ i ] ) ++ alt_ref_sum ;
 }
 if ( alt_ref_sum > REF_FRAMES - cfg -> ss_number_layers * cfg -> ts_number_layers ) ERROR ( "Not enough ref buffers for svc alt ref frames" ) ;
 if ( ( cfg -> ss_number_layers > 3 || cfg -> ss_number_layers * cfg -> ts_number_layers > 4 ) && cfg -> g_error_resilient == 0 ) ERROR ( "Multiple frame context are not supported for more than 3 spatial " "layers or more than 4 spatial x temporal layers" ) ;
 }

 RANGE_CHECK_BOOL ( extra_cfg , enable_auto_alt_ref ) ;
 RANGE_CHECK ( extra_cfg , cpu_used , - 16 , 16 ) ;
 RANGE_CHECK_HI ( extra_cfg , noise_sensitivity , 6 ) ;
 RANGE_CHECK ( extra_cfg , tile_columns , 0 , 6 ) ;
 RANGE_CHECK ( extra_cfg , tile_rows , 0 , 2 ) ;
 RANGE_CHECK_HI ( extra_cfg , sharpness , 7 ) ;
 RANGE_CHECK ( extra_cfg , arnr_max_frames , 0 , 15 ) ;
 RANGE_CHECK_HI ( extra_cfg , arnr_strength , 6 ) ;
 RANGE_CHECK ( extra_cfg , cq_level , 0 , 63 ) ;
 RANGE_CHECK ( cfg , g_bit_depth , VPX_BITS_8 , VPX_BITS_12 ) ;
 RANGE_CHECK ( cfg , g_input_bit_depth , 8 , 12 ) ;
 RANGE_CHECK ( extra_cfg , content , VP9E_CONTENT_DEFAULT , VP9E_CONTENT_INVALID - 1 ) ;
 if ( extra_cfg -> tuning == VP8_TUNE_SSIM ) ERROR ( "Option --tune=ssim is not currently supported in VP9." ) ;
 if ( cfg -> g_pass == VPX_RC_LAST_PASS ) {
 const size_t packet_sz = sizeof ( FIRSTPASS_STATS ) ;
 const int n_packets = ( int ) ( cfg -> rc_twopass_stats_in . sz / packet_sz ) ;
 const FIRSTPASS_STATS * stats ;
 if ( cfg -> rc_twopass_stats_in . buf == NULL ) ERROR ( "rc_twopass_stats_in.buf not set." ) ;
 if ( cfg -> rc_twopass_stats_in . sz % packet_sz ) ERROR ( "rc_twopass_stats_in.sz indicates truncated packet." ) ;
 if ( cfg -> ss_number_layers > 1 || cfg -> ts_number_layers > 1 ) {
 int i ;
 unsigned int n_packets_per_layer [ VPX_SS_MAX_LAYERS ] = {
 0 }
 ;
 stats = cfg -> rc_twopass_stats_in . buf ;
 for ( i = 0 ;
 i < n_packets ;
 ++ i ) {
 const int layer_id = ( int ) stats [ i ] . spatial_layer_id ;
 if ( layer_id >= 0 && layer_id < ( int ) cfg -> ss_number_layers ) {
 ++ n_packets_per_layer [ layer_id ] ;
 }
 }
 for ( i = 0 ;
 i < ( int ) cfg -> ss_number_layers ;
 ++ i ) {
 unsigned int layer_id ;
 if ( n_packets_per_layer [ i ] < 2 ) {
 ERROR ( "rc_twopass_stats_in requires at least two packets for each " "layer." ) ;
 }
 stats = ( const FIRSTPASS_STATS * ) cfg -> rc_twopass_stats_in . buf + n_packets - cfg -> ss_number_layers + i ;
 layer_id = ( int ) stats -> spatial_layer_id ;
 if ( layer_id >= cfg -> ss_number_layers || ( unsigned int ) ( stats -> count + 0.5 ) != n_packets_per_layer [ layer_id ] - 1 ) ERROR ( "rc_twopass_stats_in missing EOS stats packet" ) ;
 }
 }
 else {
 if ( cfg -> rc_twopass_stats_in . sz < 2 * packet_sz ) ERROR ( "rc_twopass_stats_in requires at least two packets." ) ;
 stats = ( const FIRSTPASS_STATS * ) cfg -> rc_twopass_stats_in . buf + n_packets - 1 ;
 if ( ( int ) ( stats -> count + 0.5 ) != n_packets - 1 ) ERROR ( "rc_twopass_stats_in missing EOS stats packet" ) ;
 }
 }


 if ( cfg -> g_profile > ( unsigned int ) PROFILE_1 && extra_cfg -> bit_depth == VPX_BITS_8 ) ERROR ( "Codec bit-depth 8 not supported in profile > 1" ) ;
 return VPX_CODEC_OK ;
 }
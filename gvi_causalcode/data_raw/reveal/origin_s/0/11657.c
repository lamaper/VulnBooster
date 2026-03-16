void vp8_change_config ( VP8_COMP * cpi , VP8_CONFIG * oxcf ) {
 VP8_COMMON * cm = & cpi -> common ;
 int last_w , last_h , prev_number_of_layers ;
 if ( ! cpi ) return ;
 if ( ! oxcf ) return ;

 sem_wait ( & cpi -> h_event_end_lpf ) ;
 cpi -> b_lpf_running = 0 ;
 }

 cm -> version = oxcf -> Version ;
 vp8_setup_version ( cm ) ;
 }
 last_w = cpi -> oxcf . Width ;
 last_h = cpi -> oxcf . Height ;
 prev_number_of_layers = cpi -> oxcf . number_of_layers ;
 cpi -> oxcf = * oxcf ;
 switch ( cpi -> oxcf . Mode ) {
 case MODE_REALTIME : cpi -> pass = 0 ;
 cpi -> compressor_speed = 2 ;
 if ( cpi -> oxcf . cpu_used < - 16 ) {
 cpi -> oxcf . cpu_used = - 16 ;
 }
 if ( cpi -> oxcf . cpu_used > 16 ) cpi -> oxcf . cpu_used = 16 ;
 break ;
 case MODE_GOODQUALITY : cpi -> pass = 0 ;
 cpi -> compressor_speed = 1 ;
 if ( cpi -> oxcf . cpu_used < - 5 ) {
 cpi -> oxcf . cpu_used = - 5 ;
 }
 if ( cpi -> oxcf . cpu_used > 5 ) cpi -> oxcf . cpu_used = 5 ;
 break ;
 case MODE_BESTQUALITY : cpi -> pass = 0 ;
 cpi -> compressor_speed = 0 ;
 break ;
 case MODE_FIRSTPASS : cpi -> pass = 1 ;
 cpi -> compressor_speed = 1 ;
 break ;
 case MODE_SECONDPASS : cpi -> pass = 2 ;
 cpi -> compressor_speed = 1 ;
 if ( cpi -> oxcf . cpu_used < - 5 ) {
 cpi -> oxcf . cpu_used = - 5 ;
 }
 if ( cpi -> oxcf . cpu_used > 5 ) cpi -> oxcf . cpu_used = 5 ;
 break ;
 case MODE_SECONDPASS_BEST : cpi -> pass = 2 ;
 cpi -> compressor_speed = 0 ;
 break ;
 }
 if ( cpi -> pass == 0 ) cpi -> auto_worst_q = 1 ;
 cpi -> oxcf . worst_allowed_q = q_trans [ oxcf -> worst_allowed_q ] ;
 cpi -> oxcf . best_allowed_q = q_trans [ oxcf -> best_allowed_q ] ;
 cpi -> oxcf . cq_level = q_trans [ cpi -> oxcf . cq_level ] ;
 if ( oxcf -> fixed_q >= 0 ) {
 if ( oxcf -> worst_allowed_q < 0 ) cpi -> oxcf . fixed_q = q_trans [ 0 ] ;
 else cpi -> oxcf . fixed_q = q_trans [ oxcf -> worst_allowed_q ] ;
 if ( oxcf -> alt_q < 0 ) cpi -> oxcf . alt_q = q_trans [ 0 ] ;
 else cpi -> oxcf . alt_q = q_trans [ oxcf -> alt_q ] ;
 if ( oxcf -> key_q < 0 ) cpi -> oxcf . key_q = q_trans [ 0 ] ;
 else cpi -> oxcf . key_q = q_trans [ oxcf -> key_q ] ;
 if ( oxcf -> gold_q < 0 ) cpi -> oxcf . gold_q = q_trans [ 0 ] ;
 else cpi -> oxcf . gold_q = q_trans [ oxcf -> gold_q ] ;
 }
 cpi -> baseline_gf_interval = cpi -> oxcf . alt_freq ? cpi -> oxcf . alt_freq : DEFAULT_GF_INTERVAL ;
 cpi -> ref_frame_flags = VP8_ALTR_FRAME | VP8_GOLD_FRAME | VP8_LAST_FRAME ;
 cm -> refresh_golden_frame = 0 ;
 cm -> refresh_last_frame = 1 ;
 cm -> refresh_entropy_probs = 1 ;


 setup_features ( cpi ) ;
 {
 int i ;
 for ( i = 0 ;
 i < MAX_MB_SEGMENTS ;
 i ++ ) cpi -> segment_encode_breakout [ i ] = cpi -> oxcf . encode_breakout ;
 }
 if ( cpi -> oxcf . fixed_q > MAXQ ) cpi -> oxcf . fixed_q = MAXQ ;
 if ( cpi -> oxcf . end_usage == USAGE_LOCAL_FILE_PLAYBACK ) {
 cpi -> oxcf . starting_buffer_level = 60000 ;
 cpi -> oxcf . optimal_buffer_level = 60000 ;
 cpi -> oxcf . maximum_buffer_size = 240000 ;
 cpi -> oxcf . starting_buffer_level_in_ms = 60000 ;
 cpi -> oxcf . optimal_buffer_level_in_ms = 60000 ;
 cpi -> oxcf . maximum_buffer_size_in_ms = 240000 ;
 }
 cpi -> oxcf . target_bandwidth *= 1000 ;
 cpi -> oxcf . starting_buffer_level = rescale ( ( int ) cpi -> oxcf . starting_buffer_level , cpi -> oxcf . target_bandwidth , 1000 ) ;
 if ( cpi -> oxcf . optimal_buffer_level == 0 ) cpi -> oxcf . optimal_buffer_level = cpi -> oxcf . target_bandwidth / 8 ;
 else cpi -> oxcf . optimal_buffer_level = rescale ( ( int ) cpi -> oxcf . optimal_buffer_level , cpi -> oxcf . target_bandwidth , 1000 ) ;
 if ( cpi -> oxcf . maximum_buffer_size == 0 ) cpi -> oxcf . maximum_buffer_size = cpi -> oxcf . target_bandwidth / 8 ;
 else cpi -> oxcf . maximum_buffer_size = rescale ( ( int ) cpi -> oxcf . maximum_buffer_size , cpi -> oxcf . target_bandwidth , 1000 ) ;
 if ( cpi -> bits_off_target > cpi -> oxcf . maximum_buffer_size ) {
 cpi -> bits_off_target = cpi -> oxcf . maximum_buffer_size ;
 cpi -> buffer_level = cpi -> bits_off_target ;
 }
 vp8_new_framerate ( cpi , cpi -> framerate ) ;
 cpi -> worst_quality = cpi -> oxcf . worst_allowed_q ;
 cpi -> best_quality = cpi -> oxcf . best_allowed_q ;
 if ( cpi -> active_worst_quality > cpi -> oxcf . worst_allowed_q ) {
 cpi -> active_worst_quality = cpi -> oxcf . worst_allowed_q ;
 }
 else if ( cpi -> active_worst_quality < cpi -> oxcf . best_allowed_q ) {
 cpi -> active_worst_quality = cpi -> oxcf . best_allowed_q ;
 }
 if ( cpi -> active_best_quality < cpi -> oxcf . best_allowed_q ) {
 cpi -> active_best_quality = cpi -> oxcf . best_allowed_q ;
 }
 else if ( cpi -> active_best_quality > cpi -> oxcf . worst_allowed_q ) {
 cpi -> active_best_quality = cpi -> oxcf . worst_allowed_q ;
 }
 cpi -> buffered_mode = cpi -> oxcf . optimal_buffer_level > 0 ;
 cpi -> cq_target_quality = cpi -> oxcf . cq_level ;
 cpi -> drop_frames_allowed = cpi -> oxcf . allow_df && cpi -> buffered_mode ;
 cpi -> target_bandwidth = cpi -> oxcf . target_bandwidth ;
 if ( cpi -> oxcf . number_of_layers != prev_number_of_layers ) {
 cpi -> temporal_pattern_counter = 0 ;
 reset_temporal_layer_change ( cpi , oxcf , prev_number_of_layers ) ;
 }
 cm -> Width = cpi -> oxcf . Width ;
 cm -> Height = cpi -> oxcf . Height ;
 if ( cpi -> oxcf . Sharpness > 7 ) cpi -> oxcf . Sharpness = 7 ;
 cm -> sharpness_level = cpi -> oxcf . Sharpness ;
 if ( cm -> horiz_scale != NORMAL || cm -> vert_scale != NORMAL ) {
 int UNINITIALIZED_IS_SAFE ( hr ) , UNINITIALIZED_IS_SAFE ( hs ) ;
 int UNINITIALIZED_IS_SAFE ( vr ) , UNINITIALIZED_IS_SAFE ( vs ) ;
 Scale2Ratio ( cm -> horiz_scale , & hr , & hs ) ;
 Scale2Ratio ( cm -> vert_scale , & vr , & vs ) ;
 cm -> Width = ( hs - 1 + cpi -> oxcf . Width * hr ) / hs ;
 cm -> Height = ( vs - 1 + cpi -> oxcf . Height * vr ) / vs ;
 }
 if ( last_w != cpi -> oxcf . Width || last_h != cpi -> oxcf . Height ) cpi -> force_next_frame_intra = 1 ;
 if ( ( ( cm -> Width + 15 ) & 0xfffffff0 ) != cm -> yv12_fb [ cm -> lst_fb_idx ] . y_width || ( ( cm -> Height + 15 ) & 0xfffffff0 ) != cm -> yv12_fb [ cm -> lst_fb_idx ] . y_height || cm -> yv12_fb [ cm -> lst_fb_idx ] . y_width == 0 ) {
 dealloc_raw_frame_buffers ( cpi ) ;
 alloc_raw_frame_buffers ( cpi ) ;
 vp8_alloc_compressor_data ( cpi ) ;
 }
 if ( cpi -> oxcf . fixed_q >= 0 ) {
 cpi -> last_q [ 0 ] = cpi -> oxcf . fixed_q ;
 cpi -> last_q [ 1 ] = cpi -> oxcf . fixed_q ;
 }
 cpi -> Speed = cpi -> oxcf . cpu_used ;
 if ( cpi -> oxcf . lag_in_frames == 0 ) {
 cpi -> oxcf . allow_lag = 0 ;
 }
 else if ( cpi -> oxcf . lag_in_frames > MAX_LAG_BUFFERS ) cpi -> oxcf . lag_in_frames = MAX_LAG_BUFFERS ;
 cpi -> alt_ref_source = NULL ;
 cpi -> is_src_frame_alt_ref = 0 ;

 if ( ! cpi -> denoiser . yv12_mc_running_avg . buffer_alloc ) {
 int width = ( cpi -> oxcf . Width + 15 ) & ~ 15 ;
 int height = ( cpi -> oxcf . Height + 15 ) & ~ 15 ;
 vp8_denoiser_allocate ( & cpi -> denoiser , width , height , cm -> mb_rows , cm -> mb_cols , cpi -> oxcf . noise_sensitivity ) ;
 }
 }

 cpi -> last_frame_distortion = 0 ;

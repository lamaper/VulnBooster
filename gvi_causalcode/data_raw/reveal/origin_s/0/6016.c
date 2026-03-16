static void init_config ( VP8_COMP * cpi , VP8_CONFIG * oxcf ) {
 VP8_COMMON * cm = & cpi -> common ;
 cpi -> oxcf = * oxcf ;
 cpi -> auto_gold = 1 ;
 cpi -> auto_adjust_gold_quantizer = 1 ;
 cm -> version = oxcf -> Version ;
 vp8_setup_version ( cm ) ;
 cpi -> framerate = ( double ) ( oxcf -> timebase . den ) / ( double ) ( oxcf -> timebase . num ) ;
 if ( cpi -> framerate > 180 ) cpi -> framerate = 30 ;
 cpi -> ref_framerate = cpi -> framerate ;
 vp8_change_config ( cpi , oxcf ) ;
 cpi -> active_worst_quality = cpi -> oxcf . worst_allowed_q ;
 cpi -> active_best_quality = cpi -> oxcf . best_allowed_q ;
 cpi -> avg_frame_qindex = cpi -> oxcf . worst_allowed_q ;
 cpi -> buffer_level = cpi -> oxcf . starting_buffer_level ;
 cpi -> bits_off_target = cpi -> oxcf . starting_buffer_level ;
 cpi -> rolling_target_bits = cpi -> av_per_frame_bandwidth ;
 cpi -> rolling_actual_bits = cpi -> av_per_frame_bandwidth ;
 cpi -> long_rolling_target_bits = cpi -> av_per_frame_bandwidth ;
 cpi -> long_rolling_actual_bits = cpi -> av_per_frame_bandwidth ;
 cpi -> total_actual_bits = 0 ;
 cpi -> total_target_vs_actual = 0 ;
 if ( cpi -> oxcf . number_of_layers > 1 ) {
 unsigned int i ;
 double prev_layer_framerate = 0 ;
 for ( i = 0 ;
 i < cpi -> oxcf . number_of_layers ;
 i ++ ) {
 init_temporal_layer_context ( cpi , oxcf , i , prev_layer_framerate ) ;
 prev_layer_framerate = cpi -> output_framerate / cpi -> oxcf . rate_decimator [ i ] ;
 }
 }

 int i ;
 cpi -> fixed_divide [ 0 ] = 0 ;
 for ( i = 1 ;
 i < 512 ;
 i ++ ) cpi -> fixed_divide [ i ] = 0x80000 / i ;
 }

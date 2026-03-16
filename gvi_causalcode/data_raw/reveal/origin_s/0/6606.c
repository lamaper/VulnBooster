void vp9_update_spatial_layer_framerate ( VP9_COMP * const cpi , double framerate ) {
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 LAYER_CONTEXT * const lc = get_layer_context ( cpi ) ;
 RATE_CONTROL * const lrc = & lc -> rc ;
 lc -> framerate = framerate ;
 lrc -> avg_frame_bandwidth = ( int ) ( lc -> target_bandwidth / lc -> framerate ) ;
 lrc -> min_frame_bandwidth = ( int ) ( lrc -> avg_frame_bandwidth * oxcf -> two_pass_vbrmin_section / 100 ) ;
 lrc -> max_frame_bandwidth = ( int ) ( ( ( int64_t ) lrc -> avg_frame_bandwidth * oxcf -> two_pass_vbrmax_section ) / 100 ) ;
 vp9_rc_set_gf_max_interval ( cpi , lrc ) ;
 }
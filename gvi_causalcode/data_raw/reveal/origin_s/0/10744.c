void vp9_rc_update_framerate ( VP9_COMP * cpi ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 int vbr_max_bits ;
 rc -> avg_frame_bandwidth = ( int ) ( oxcf -> target_bandwidth / cpi -> framerate ) ;
 rc -> min_frame_bandwidth = ( int ) ( rc -> avg_frame_bandwidth * oxcf -> two_pass_vbrmin_section / 100 ) ;
 rc -> min_frame_bandwidth = MAX ( rc -> min_frame_bandwidth , FRAME_OVERHEAD_BITS ) ;
 vbr_max_bits = ( int ) ( ( ( int64_t ) rc -> avg_frame_bandwidth * oxcf -> two_pass_vbrmax_section ) / 100 ) ;
 rc -> max_frame_bandwidth = MAX ( MAX ( ( cm -> MBs * MAX_MB_RATE ) , MAXRATE_1080P ) , vbr_max_bits ) ;
 vp9_rc_set_gf_max_interval ( cpi , rc ) ;
 }
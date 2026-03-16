void vp9_init_second_pass ( VP9_COMP * cpi ) {
 SVC * const svc = & cpi -> svc ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 const int is_two_pass_svc = ( svc -> number_spatial_layers > 1 ) || ( svc -> number_temporal_layers > 1 ) ;
 TWO_PASS * const twopass = is_two_pass_svc ? & svc -> layer_context [ svc -> spatial_layer_id ] . twopass : & cpi -> twopass ;
 double frame_rate ;
 FIRSTPASS_STATS * stats ;
 zero_stats ( & twopass -> total_stats ) ;
 zero_stats ( & twopass -> total_left_stats ) ;
 if ( ! twopass -> stats_in_end ) return ;
 stats = & twopass -> total_stats ;
 * stats = * twopass -> stats_in_end ;
 twopass -> total_left_stats = * stats ;
 frame_rate = 10000000.0 * stats -> count / stats -> duration ;
 if ( is_two_pass_svc ) {
 vp9_update_spatial_layer_framerate ( cpi , frame_rate ) ;
 twopass -> bits_left = ( int64_t ) ( stats -> duration * svc -> layer_context [ svc -> spatial_layer_id ] . target_bandwidth / 10000000.0 ) ;
 }
 else {
 vp9_new_framerate ( cpi , frame_rate ) ;
 twopass -> bits_left = ( int64_t ) ( stats -> duration * oxcf -> target_bandwidth / 10000000.0 ) ;
 }
 if ( ! is_two_pass_svc ) {
 twopass -> kf_intra_err_min = KF_MB_INTRA_MIN * cpi -> common . MBs ;
 twopass -> gf_intra_err_min = GF_MB_INTRA_MIN * cpi -> common . MBs ;
 }
 twopass -> sr_update_lag = 1 ;
 {
 const double avg_error = stats -> coded_error / DOUBLE_DIVIDE_CHECK ( stats -> count ) ;
 const FIRSTPASS_STATS * s = twopass -> stats_in ;
 double modified_error_total = 0.0 ;
 twopass -> modified_error_min = ( avg_error * oxcf -> two_pass_vbrmin_section ) / 100 ;
 twopass -> modified_error_max = ( avg_error * oxcf -> two_pass_vbrmax_section ) / 100 ;
 while ( s < twopass -> stats_in_end ) {
 modified_error_total += calculate_modified_err ( twopass , oxcf , s ) ;
 ++ s ;
 }
 twopass -> modified_error_left = modified_error_total ;
 }
 cpi -> rc . vbr_bits_off_target = 0 ;
 }
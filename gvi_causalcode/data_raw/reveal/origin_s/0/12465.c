static void show_stream_config ( struct stream_state * stream , struct VpxEncoderConfig * global , struct VpxInputContext * input ) {

 fprintf ( stderr , "Codec: %s\n" , vpx_codec_iface_name ( global -> codec -> codec_interface ( ) ) ) ;
 fprintf ( stderr , "Source file: %s File Type: %s Format: %s\n" , input -> filename , file_type_to_string ( input -> file_type ) , image_format_to_string ( input -> fmt ) ) ;
 }
 if ( stream -> next || stream -> index ) fprintf ( stderr , "\nStream Index: %d\n" , stream -> index ) ;
 fprintf ( stderr , "Destination file: %s\n" , stream -> config . out_fn ) ;
 fprintf ( stderr , "Encoder parameters:\n" ) ;
 SHOW ( g_usage ) ;
 SHOW ( g_threads ) ;
 SHOW ( g_profile ) ;
 SHOW ( g_w ) ;
 SHOW ( g_h ) ;
 SHOW ( g_bit_depth ) ;
 SHOW ( g_input_bit_depth ) ;
 SHOW ( g_timebase . num ) ;
 SHOW ( g_timebase . den ) ;
 SHOW ( g_error_resilient ) ;
 SHOW ( g_pass ) ;
 SHOW ( g_lag_in_frames ) ;
 SHOW ( rc_dropframe_thresh ) ;
 SHOW ( rc_resize_allowed ) ;
 SHOW ( rc_scaled_width ) ;
 SHOW ( rc_scaled_height ) ;
 SHOW ( rc_resize_up_thresh ) ;
 SHOW ( rc_resize_down_thresh ) ;
 SHOW ( rc_end_usage ) ;
 SHOW ( rc_target_bitrate ) ;
 SHOW ( rc_min_quantizer ) ;
 SHOW ( rc_max_quantizer ) ;
 SHOW ( rc_undershoot_pct ) ;
 SHOW ( rc_overshoot_pct ) ;
 SHOW ( rc_buf_sz ) ;
 SHOW ( rc_buf_initial_sz ) ;
 SHOW ( rc_buf_optimal_sz ) ;
 SHOW ( rc_2pass_vbr_bias_pct ) ;
 SHOW ( rc_2pass_vbr_minsection_pct ) ;
 SHOW ( rc_2pass_vbr_maxsection_pct ) ;
 SHOW ( kf_mode ) ;
 SHOW ( kf_min_dist ) ;
 SHOW ( kf_max_dist ) ;
 }
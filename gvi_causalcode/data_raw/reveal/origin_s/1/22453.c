static void encode_frame_to_data_rate ( VP9_COMP * cpi , size_t * size , uint8_t * dest , unsigned int * frame_flags ) {
 VP9_COMMON * const cm = & cpi -> common ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 struct segmentation * const seg = & cm -> seg ;
 TX_SIZE t ;
 int q ;
 int top_index ;
 int bottom_index ;
 set_ext_overrides ( cpi ) ;
 cpi -> Source = vp9_scale_if_required ( cm , cpi -> un_scaled_source , & cpi -> scaled_source ) ;
 if ( cpi -> unscaled_last_source != NULL ) cpi -> Last_Source = vp9_scale_if_required ( cm , cpi -> unscaled_last_source , & cpi -> scaled_last_source ) ;
 vp9_scale_references ( cpi ) ;
 vp9_clear_system_state ( ) ;
 cpi -> zbin_mode_boost = 0 ;
 cpi -> zbin_mode_boost_enabled = 0 ;
 set_arf_sign_bias ( cpi ) ;
 cm -> lf . mode_ref_delta_update = 0 ;
 set_mv_search_params ( cpi ) ;
 if ( cpi -> oxcf . pass == 2 && cpi -> sf . adaptive_interp_filter_search ) cpi -> sf . interp_filter_search_mask = setup_interp_filter_search_mask ( cpi ) ;
 if ( frame_is_intra_only ( cm ) ) {
 vp9_reset_segment_features ( & cm -> seg ) ;
 if ( seg -> enabled ) {
 seg -> update_map = 1 ;
 seg -> update_data = 1 ;
 }
 cpi -> rc . source_alt_ref_active = 0 ;
 cm -> error_resilient_mode = oxcf -> error_resilient_mode ;
 if ( cm -> error_resilient_mode ) {
 cm -> frame_parallel_decoding_mode = 1 ;
 cm -> reset_frame_context = 0 ;
 cm -> refresh_frame_context = 0 ;
 }
 else if ( cm -> intra_only ) {
 cm -> frame_parallel_decoding_mode = oxcf -> frame_parallel_decoding_mode ;
 cm -> reset_frame_context = 2 ;
 }
 }
 if ( is_two_pass_svc ( cpi ) && cm -> error_resilient_mode == 0 ) {
 cm -> frame_context_idx = cpi -> svc . spatial_layer_id * cpi -> svc . number_temporal_layers + cpi -> svc . temporal_layer_id ;
 if ( cpi -> svc . number_temporal_layers == 1 ) {
 if ( cpi -> svc . spatial_layer_id == 0 && cpi -> svc . layer_context [ 0 ] . last_frame_type == KEY_FRAME ) cm -> frame_parallel_decoding_mode = 1 ;
 else cm -> frame_parallel_decoding_mode = 0 ;
 }
 else if ( cpi -> svc . spatial_layer_id == 0 ) {
 int i ;
 for ( i = 0 ;
 i < cpi -> svc . number_temporal_layers ;
 ++ i ) {
 if ( cpi -> svc . layer_context [ 0 ] . frames_from_key_frame == 1 << i ) {
 cm -> frame_parallel_decoding_mode = 1 ;
 break ;
 }
 }
 if ( i == cpi -> svc . number_temporal_layers ) cm -> frame_parallel_decoding_mode = 0 ;
 }
 }
 if ( oxcf -> pass == 2 && cpi -> sf . static_segmentation ) configure_static_seg_features ( cpi ) ;
 if ( oxcf -> pass == 2 && ( ! cpi -> use_svc || is_two_pass_svc ( cpi ) ) ) {
 cpi -> skippable_frame = is_skippable_frame ( cpi ) ;
 }
 if ( oxcf -> pass == 0 && oxcf -> rc_mode == VPX_CBR && cm -> frame_type != KEY_FRAME ) {
 if ( vp9_rc_drop_frame ( cpi ) ) {
 vp9_rc_postencode_update_drop_frame ( cpi ) ;
 ++ cm -> current_video_frame ;
 return ;
 }
 }
 vp9_clear_system_state ( ) ;

 int l = 0 ;
 switch ( oxcf -> noise_sensitivity ) {
 case 1 : l = 20 ;
 break ;
 case 2 : l = 40 ;
 break ;
 case 3 : l = 60 ;
 break ;
 case 4 : case 5 : l = 100 ;
 break ;
 case 6 : l = 150 ;
 break ;
 }
 vp9_denoise ( cpi -> Source , cpi -> Source , l ) ;
 }

 for ( i = 0 ;
 i < MAX_MODES ;
 ++ i ) cpi -> mode_chosen_counts [ i ] = 0 ;

 vp9_set_rd_speed_thresholds ( cpi ) ;
 vp9_set_rd_speed_thresholds_sub8x8 ( cpi ) ;
 q = vp9_rc_pick_q_and_bounds ( cpi , & bottom_index , & top_index ) ;
 if ( ! frame_is_intra_only ( cm ) ) {
 cm -> interp_filter = cpi -> sf . default_interp_filter ;
 vp9_set_high_precision_mv ( cpi , q < HIGH_PRECISION_MV_QTHRESH ) ;
 }
 if ( cpi -> sf . recode_loop == DISALLOW_RECODE ) {
 encode_without_recode_loop ( cpi , q ) ;
 }
 else {
 encode_with_recode_loop ( cpi , size , dest , q , bottom_index , top_index ) ;
 }

 vp9_write_yuv_frame_420 ( & cpi -> denoiser . running_avg_y [ INTRA_FRAME ] , yuv_denoised_file ) ;
 }

 cpi -> ambient_err = vp9_get_y_sse ( cpi -> Source , get_frame_new_buffer ( cm ) ) ;
 }
 if ( cm -> frame_type == KEY_FRAME ) cpi -> refresh_last_frame = 1 ;
 cm -> frame_to_show = get_frame_new_buffer ( cm ) ;
 loopfilter_frame ( cpi , cm ) ;
 vp9_pack_bitstream ( cpi , dest , size ) ;
 if ( cm -> seg . update_map ) update_reference_segmentation_map ( cpi ) ;
 release_scaled_references ( cpi ) ;
 vp9_update_reference_frames ( cpi ) ;
 for ( t = TX_4X4 ;
 t <= TX_32X32 ;
 t ++ ) full_to_model_counts ( cm -> counts . coef [ t ] , cpi -> coef_counts [ t ] ) ;
 if ( ! cm -> error_resilient_mode && ! cm -> frame_parallel_decoding_mode ) vp9_adapt_coef_probs ( cm ) ;
 if ( ! frame_is_intra_only ( cm ) ) {
 if ( ! cm -> error_resilient_mode && ! cm -> frame_parallel_decoding_mode ) {
 vp9_adapt_mode_probs ( cm ) ;
 vp9_adapt_mv_probs ( cm , cm -> allow_high_precision_mv ) ;
 }
 }
 if ( cpi -> refresh_golden_frame == 1 ) cpi -> frame_flags |= FRAMEFLAGS_GOLDEN ;
 else cpi -> frame_flags &= ~ FRAMEFLAGS_GOLDEN ;
 if ( cpi -> refresh_alt_ref_frame == 1 ) cpi -> frame_flags |= FRAMEFLAGS_ALTREF ;
 else cpi -> frame_flags &= ~ FRAMEFLAGS_ALTREF ;
 cpi -> ref_frame_flags = get_ref_frame_flags ( cpi ) ;
 cm -> last_frame_type = cm -> frame_type ;
 vp9_rc_postencode_update ( cpi , * size ) ;


 * frame_flags = cpi -> frame_flags | FRAMEFLAGS_KEY ;
 }
 else {
 * frame_flags = cpi -> frame_flags & ~ FRAMEFLAGS_KEY ;
 }
 cm -> seg . update_map = 0 ;
 cm -> seg . update_data = 0 ;
 cm -> lf . mode_ref_delta_update = 0 ;
 cm -> last_width = cm -> width ;
 cm -> last_height = cm -> height ;
 if ( ! cm -> show_existing_frame ) {
 if ( is_two_pass_svc ( cpi ) && cm -> error_resilient_mode == 0 ) cm -> last_show_frame = 0 ;
 else cm -> last_show_frame = cm -> show_frame ;
 }
 if ( cm -> show_frame ) {
 vp9_swap_mi_and_prev_mi ( cm ) ;
 ++ cm -> current_video_frame ;
 if ( cpi -> use_svc ) vp9_inc_frame_in_layer ( cpi ) ;
 }
 if ( is_two_pass_svc ( cpi ) ) cpi -> svc . layer_context [ cpi -> svc . spatial_layer_id ] . last_frame_type = cm -> frame_type ;
 }
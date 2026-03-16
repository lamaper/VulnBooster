int vp9_get_compressed_data ( VP9_COMP * cpi , unsigned int * frame_flags , size_t * size , uint8_t * dest , int64_t * time_stamp , int64_t * time_end , int flush ) {
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCKD * const xd = & cpi -> mb . e_mbd ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 struct vpx_usec_timer cmptimer ;
 YV12_BUFFER_CONFIG * force_src_buffer = NULL ;
 struct lookahead_entry * last_source = NULL ;
 struct lookahead_entry * source = NULL ;
 MV_REFERENCE_FRAME ref_frame ;
 int arf_src_index ;
 if ( is_two_pass_svc ( cpi ) ) {


 }
 vpx_usec_timer_start ( & cmptimer ) ;
 vp9_set_high_precision_mv ( cpi , ALTREF_HIGH_PRECISION_MV ) ;
 cm -> reset_frame_context = 0 ;
 cm -> refresh_frame_context = 1 ;
 cpi -> refresh_last_frame = 1 ;
 cpi -> refresh_golden_frame = 0 ;
 cpi -> refresh_alt_ref_frame = 0 ;
 arf_src_index = get_arf_src_index ( cpi ) ;
 if ( arf_src_index ) {
 assert ( arf_src_index <= rc -> frames_to_key ) ;
 if ( ( source = vp9_lookahead_peek ( cpi -> lookahead , arf_src_index ) ) != NULL ) {
 cpi -> alt_ref_source = source ;

 int i ;
 for ( i = cpi -> svc . spatial_layer_id - 1 ;
 i >= 0 ;
 -- i ) {
 if ( oxcf -> ss_play_alternate [ i ] ) {
 cpi -> gld_fb_idx = cpi -> svc . layer_context [ i ] . alt_ref_idx ;
 break ;
 }
 }
 }
 cpi -> svc . layer_context [ cpi -> svc . spatial_layer_id ] . has_alt_frame = 1 ;

 vp9_temporal_filter ( cpi , arf_src_index ) ;
 vp9_extend_frame_borders ( & cpi -> alt_ref_buffer ) ;
 force_src_buffer = & cpi -> alt_ref_buffer ;
 }
 cm -> show_frame = 0 ;
 cpi -> refresh_alt_ref_frame = 1 ;
 cpi -> refresh_golden_frame = 0 ;
 cpi -> refresh_last_frame = 0 ;
 rc -> is_src_frame_alt_ref = 0 ;
 rc -> source_alt_ref_pending = 0 ;
 }
 else {
 rc -> source_alt_ref_pending = 0 ;
 }
 }
 if ( ! source ) {
 if ( cm -> current_video_frame > 0 ) {
 if ( ( last_source = vp9_lookahead_peek ( cpi -> lookahead , - 1 ) ) == NULL ) return - 1 ;
 }

 else # endif source = vp9_lookahead_pop ( cpi -> lookahead , flush ) ;
 if ( source != NULL ) {
 cm -> show_frame = 1 ;
 cm -> intra_only = 0 ;
 check_src_altref ( cpi , source ) ;
 }
 }
 if ( source ) {
 cpi -> un_scaled_source = cpi -> Source = force_src_buffer ? force_src_buffer : & source -> img ;
 cpi -> unscaled_last_source = last_source != NULL ? & last_source -> img : NULL ;
 * time_stamp = source -> ts_start ;
 * time_end = source -> ts_end ;
 * frame_flags = ( source -> flags & VPX_EFLAG_FORCE_KF ) ? FRAMEFLAGS_KEY : 0 ;
 }
 else {
 * size = 0 ;
 if ( flush && oxcf -> pass == 1 && ! cpi -> twopass . first_pass_done ) {
 vp9_end_first_pass ( cpi ) ;
 cpi -> twopass . first_pass_done = 1 ;
 }
 return - 1 ;
 }
 if ( source -> ts_start < cpi -> first_time_stamp_ever ) {
 cpi -> first_time_stamp_ever = source -> ts_start ;
 cpi -> last_end_time_stamp_seen = source -> ts_start ;
 }
 vp9_clear_system_state ( ) ;
 if ( cm -> show_frame ) {
 adjust_frame_rate ( cpi , source ) ;
 }
 if ( cpi -> svc . number_temporal_layers > 1 && oxcf -> rc_mode == VPX_CBR ) {
 vp9_update_temporal_layer_framerate ( cpi ) ;
 vp9_restore_layer_context ( cpi ) ;
 }
 * size = 0 ;
 cm -> frame_bufs [ cm -> new_fb_idx ] . ref_count -- ;
 cm -> new_fb_idx = get_free_fb ( cm ) ;
 if ( ( oxcf -> pass == 2 ) && ( ! cpi -> use_svc || is_two_pass_svc ( cpi ) ) ) {
 vp9_rc_get_second_pass_params ( cpi ) ;
 }
 if ( ! cpi -> use_svc && cpi -> multi_arf_allowed ) {
 if ( cm -> frame_type == KEY_FRAME ) {
 init_buffer_indices ( cpi ) ;
 }
 else if ( oxcf -> pass == 2 ) {
 const GF_GROUP * const gf_group = & cpi -> twopass . gf_group ;
 cpi -> alt_fb_idx = gf_group -> arf_ref_idx [ gf_group -> index ] ;
 }
 }
 cpi -> frame_flags = * frame_flags ;
 if ( oxcf -> pass == 2 && cm -> current_video_frame == 0 && oxcf -> allow_spatial_resampling && oxcf -> rc_mode == VPX_VBR ) {
 vp9_set_size_literal ( cpi , oxcf -> scaled_frame_width , oxcf -> scaled_frame_height ) ;
 }
 vp9_realloc_frame_buffer ( get_frame_new_buffer ( cm ) , cm -> width , cm -> height , cm -> subsampling_x , cm -> subsampling_y , # if CONFIG_VP9_HIGHBITDEPTH cm -> use_highbitdepth , # endif VP9_ENC_BORDER_IN_PIXELS , NULL , NULL , NULL ) ;
 alloc_util_frame_buffers ( cpi ) ;
 init_motion_estimation ( cpi ) ;
 for ( ref_frame = LAST_FRAME ;
 ref_frame <= ALTREF_FRAME ;
 ++ ref_frame ) {
 const int idx = cm -> ref_frame_map [ get_ref_frame_idx ( cpi , ref_frame ) ] ;
 YV12_BUFFER_CONFIG * const buf = & cm -> frame_bufs [ idx ] . buf ;
 RefBuffer * const ref_buf = & cm -> frame_refs [ ref_frame - 1 ] ;
 ref_buf -> buf = buf ;
 ref_buf -> idx = idx ;



 }
 set_ref_ptrs ( cm , xd , LAST_FRAME , LAST_FRAME ) ;
 if ( oxcf -> aq_mode == VARIANCE_AQ ) {
 vp9_vaq_init ( ) ;
 }
 if ( oxcf -> pass == 1 && ( ! cpi -> use_svc || is_two_pass_svc ( cpi ) ) ) {
 const int lossless = is_lossless_requested ( oxcf ) ;

 else cpi -> mb . fwd_txm4x4 = lossless ? vp9_fwht4x4 : vp9_fdct4x4 ;
 cpi -> mb . high_itxm_add = lossless ? vp9_high_iwht4x4_add : vp9_high_idct4x4_add ;


 vp9_first_pass ( cpi , source ) ;
 }
 else if ( oxcf -> pass == 2 && ( ! cpi -> use_svc || is_two_pass_svc ( cpi ) ) ) {
 Pass2Encode ( cpi , size , dest , frame_flags ) ;
 }
 else if ( cpi -> use_svc ) {
 SvcEncode ( cpi , size , dest , frame_flags ) ;
 }
 else {
 Pass0Encode ( cpi , size , dest , frame_flags ) ;
 }
 if ( cm -> refresh_frame_context ) cm -> frame_contexts [ cm -> frame_context_idx ] = cm -> fc ;
 if ( * size == 0 ) {
 release_scaled_references ( cpi ) ;
 }
 if ( * size > 0 ) {
 cpi -> droppable = ! frame_is_reference ( cpi ) ;
 }
 if ( ( cpi -> svc . number_temporal_layers > 1 && oxcf -> rc_mode == VPX_CBR ) || ( ( cpi -> svc . number_temporal_layers > 1 || cpi -> svc . number_spatial_layers > 1 ) && oxcf -> pass == 2 ) ) {
 vp9_save_layer_context ( cpi ) ;
 }
 vpx_usec_timer_mark ( & cmptimer ) ;
 cpi -> time_compress_data += vpx_usec_timer_elapsed ( & cmptimer ) ;
 if ( cpi -> b_calculate_psnr && oxcf -> pass != 1 && cm -> show_frame ) generate_psnr_packet ( cpi ) ;

 cpi -> bytes += ( int ) ( * size ) ;
 if ( cm -> show_frame ) {
 cpi -> count ++ ;
 if ( cpi -> b_calculate_psnr ) {
 YV12_BUFFER_CONFIG * orig = cpi -> Source ;
 YV12_BUFFER_CONFIG * recon = cpi -> common . frame_to_show ;
 YV12_BUFFER_CONFIG * pp = & cm -> post_proc_buffer ;
 PSNR_STATS psnr ;
 calc_psnr ( orig , recon , & psnr ) ;
 cpi -> total += psnr . psnr [ 0 ] ;
 cpi -> total_y += psnr . psnr [ 1 ] ;
 cpi -> total_u += psnr . psnr [ 2 ] ;
 cpi -> total_v += psnr . psnr [ 3 ] ;
 cpi -> total_sq_error += psnr . sse [ 0 ] ;
 cpi -> total_samples += psnr . samples [ 0 ] ;
 {
 PSNR_STATS psnr2 ;
 double frame_ssim2 = 0 , weight = 0 ;


 calc_psnr ( orig , pp , & psnr2 ) ;
 cpi -> totalp += psnr2 . psnr [ 0 ] ;
 cpi -> totalp_y += psnr2 . psnr [ 1 ] ;
 cpi -> totalp_u += psnr2 . psnr [ 2 ] ;
 cpi -> totalp_v += psnr2 . psnr [ 3 ] ;
 cpi -> totalp_sq_error += psnr2 . sse [ 0 ] ;
 cpi -> totalp_samples += psnr2 . samples [ 0 ] ;
 frame_ssim2 = vp9_calc_ssim ( orig , recon , & weight ) ;
 cpi -> summed_quality += frame_ssim2 * weight ;
 cpi -> summed_weights += weight ;
 frame_ssim2 = vp9_calc_ssim ( orig , & cm -> post_proc_buffer , & weight ) ;
 cpi -> summedp_quality += frame_ssim2 * weight ;
 cpi -> summedp_weights += weight ;

 FILE * f = fopen ( "q_used.stt" , "a" ) ;
 fprintf ( f , "%5d : Y%f7.3:U%f7.3:V%f7.3:F%f7.3:S%7.3f\n" , cpi -> common . current_video_frame , y2 , u2 , v2 , frame_psnr2 , frame_ssim2 ) ;
 fclose ( f ) ;
 }

 }
 if ( cpi -> b_calculate_ssimg ) {
 double y , u , v , frame_all ;
 frame_all = vp9_calc_ssimg ( cpi -> Source , cm -> frame_to_show , & y , & u , & v ) ;
 cpi -> total_ssimg_y += y ;
 cpi -> total_ssimg_u += u ;
 cpi -> total_ssimg_v += v ;
 cpi -> total_ssimg_all += frame_all ;
 }
 }
 }

 ++ cpi -> svc . spatial_layer_to_encode ;
 if ( cpi -> svc . spatial_layer_to_encode >= cpi -> svc . number_spatial_layers ) cpi -> svc . spatial_layer_to_encode = 0 ;
 }
 return 0 ;
 }
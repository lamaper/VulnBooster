int vp8_get_compressed_data ( VP8_COMP * cpi , unsigned int * frame_flags , unsigned long * size , unsigned char * dest , unsigned char * dest_end , int64_t * time_stamp , int64_t * time_end , int flush ) {
 VP8_COMMON * cm ;
 struct vpx_usec_timer tsctimer ;
 struct vpx_usec_timer ticktimer ;
 struct vpx_usec_timer cmptimer ;
 YV12_BUFFER_CONFIG * force_src_buffer = NULL ;
 if ( ! cpi ) return - 1 ;
 cm = & cpi -> common ;
 if ( setjmp ( cpi -> common . error . jmp ) ) {
 cpi -> common . error . setjmp = 0 ;
 vp8_clear_system_state ( ) ;
 return VPX_CODEC_CORRUPT_FRAME ;
 }
 cpi -> common . error . setjmp = 1 ;
 vpx_usec_timer_start ( & cmptimer ) ;
 cpi -> source = NULL ;

 if ( ( cpi -> source = vp8_lookahead_peek ( cpi -> lookahead , cpi -> frames_till_gf_update_due , PEEK_FORWARD ) ) ) {
 cpi -> alt_ref_source = cpi -> source ;
 if ( cpi -> oxcf . arnr_max_frames > 0 ) {
 vp8_temporal_filter_prepare_c ( cpi , cpi -> frames_till_gf_update_due ) ;
 force_src_buffer = & cpi -> alt_ref_buffer ;
 }
 cpi -> frames_till_alt_ref_frame = cpi -> frames_till_gf_update_due ;
 cm -> refresh_alt_ref_frame = 1 ;
 cm -> refresh_golden_frame = 0 ;
 cm -> refresh_last_frame = 0 ;
 cm -> show_frame = 0 ;
 cpi -> source_alt_ref_pending = 0 ;
 cpi -> is_src_frame_alt_ref = 0 ;
 }
 }

 if ( cpi -> pass == 1 && cm -> current_video_frame > 0 ) {
 if ( ( cpi -> last_source = vp8_lookahead_peek ( cpi -> lookahead , 1 , PEEK_BACKWARD ) ) == NULL ) return - 1 ;
 }
 if ( ( cpi -> source = vp8_lookahead_pop ( cpi -> lookahead , flush ) ) ) {
 cm -> show_frame = 1 ;
 cpi -> is_src_frame_alt_ref = cpi -> alt_ref_source && ( cpi -> source == cpi -> alt_ref_source ) ;
 if ( cpi -> is_src_frame_alt_ref ) cpi -> alt_ref_source = NULL ;
 }
 }
 if ( cpi -> source ) {
 cpi -> Source = force_src_buffer ? force_src_buffer : & cpi -> source -> img ;
 cpi -> un_scaled_source = cpi -> Source ;
 * time_stamp = cpi -> source -> ts_start ;
 * time_end = cpi -> source -> ts_end ;
 * frame_flags = cpi -> source -> flags ;
 if ( cpi -> pass == 1 && cm -> current_video_frame > 0 ) {
 cpi -> last_frame_unscaled_source = & cpi -> last_source -> img ;
 }
 }
 else {
 * size = 0 ;

 vp8_end_first_pass ( cpi ) ;
 cpi -> twopass . first_pass_done = 1 ;
 }

 }
 if ( cpi -> source -> ts_start < cpi -> first_time_stamp_ever ) {
 cpi -> first_time_stamp_ever = cpi -> source -> ts_start ;
 cpi -> last_end_time_stamp_seen = cpi -> source -> ts_start ;
 }
 if ( cm -> show_frame ) {
 int64_t this_duration ;
 int step = 0 ;
 if ( cpi -> source -> ts_start == cpi -> first_time_stamp_ever ) {
 this_duration = cpi -> source -> ts_end - cpi -> source -> ts_start ;
 step = 1 ;
 }
 else {
 int64_t last_duration ;
 this_duration = cpi -> source -> ts_end - cpi -> last_end_time_stamp_seen ;
 last_duration = cpi -> last_end_time_stamp_seen - cpi -> last_time_stamp_seen ;
 if ( last_duration ) step = ( int ) ( ( ( this_duration - last_duration ) * / last_duration ) ) ;
 }
 if ( this_duration ) {
 if ( step ) cpi -> ref_framerate = 10000000.0 / this_duration ;
 else {
 double avg_duration , interval ;
 interval = ( double ) ( cpi -> source -> ts_end - cpi -> first_time_stamp_ever ) ;
 if ( interval > 10000000.0 ) interval = 10000000 ;
 avg_duration = 10000000.0 / cpi -> ref_framerate ;
 avg_duration *= ( interval - avg_duration + this_duration ) ;
 avg_duration /= interval ;
 cpi -> ref_framerate = 10000000.0 / avg_duration ;
 }
 if ( cpi -> oxcf . number_of_layers > 1 ) {
 unsigned int i ;
 assert ( cpi -> oxcf . number_of_layers <= VPX_TS_MAX_LAYERS ) ;
 for ( i = 0 ;
 i < cpi -> oxcf . number_of_layers && i < VPX_TS_MAX_LAYERS ;
 ++ i ) {
 LAYER_CONTEXT * lc = & cpi -> layer_context [ i ] ;
 lc -> framerate = cpi -> ref_framerate / cpi -> oxcf . rate_decimator [ i ] ;
 }
 }
 else vp8_new_framerate ( cpi , cpi -> ref_framerate ) ;
 }
 cpi -> last_time_stamp_seen = cpi -> source -> ts_start ;
 cpi -> last_end_time_stamp_seen = cpi -> source -> ts_end ;
 }
 if ( cpi -> oxcf . number_of_layers > 1 ) {
 int layer ;
 update_layer_contexts ( cpi ) ;
 layer = cpi -> oxcf . layer_id [ cpi -> temporal_pattern_counter % cpi -> oxcf . periodicity ] ;
 restore_layer_context ( cpi , layer ) ;
 vp8_new_framerate ( cpi , cpi -> layer_context [ layer ] . framerate ) ;
 }
 if ( cpi -> compressor_speed == 2 ) {
 vpx_usec_timer_start ( & tsctimer ) ;
 vpx_usec_timer_start ( & ticktimer ) ;
 }
 cpi -> lf_zeromv_pct = ( cpi -> zeromv_count * 100 ) / cm -> MBs ;

 int i ;
 const int num_part = ( 1 << cm -> multi_token_partition ) ;
 const unsigned long dest_size = dest_end - dest ;
 const int tok_part_buff_size = ( dest_size * 9 ) / ( 10 * num_part ) ;
 unsigned char * dp = dest ;
 cpi -> partition_d [ 0 ] = dp ;
 dp += dest_size / 10 ;
 cpi -> partition_d_end [ 0 ] = dp ;
 for ( i = 0 ;
 i < num_part ;
 i ++ ) {
 cpi -> partition_d [ i + 1 ] = dp ;
 dp += tok_part_buff_size ;
 cpi -> partition_d_end [ i + 1 ] = dp ;
 }
 }

 vp8_clear_system_state ( ) ;
 cm -> frame_type = INTER_FRAME ;
 cm -> frame_flags = * frame_flags ;

 cm -> refresh_golden_frame = 0 ;
 cm -> refresh_last_frame = 0 ;
 }
 else {
 cm -> refresh_golden_frame = 0 ;
 cm -> refresh_last_frame = 1 ;
 }

 int i = 0 ;
 for ( ;
 i < NUM_YV12_BUFFERS ;
 i ++ ) {
 if ( ! cm -> yv12_fb [ i ] . flags ) {
 cm -> new_fb_idx = i ;
 break ;
 }
 }
 assert ( i < NUM_YV12_BUFFERS ) ;
 }

 Pass1Encode ( cpi , size , dest , frame_flags ) ;
 }
 else if ( cpi -> pass == 2 ) {
 Pass2Encode ( cpi , size , dest , dest_end , frame_flags ) ;
 }
 else # endif encode_frame_to_data_rate ( cpi , size , dest , dest_end , frame_flags ) ;
 if ( cpi -> compressor_speed == 2 ) {
 unsigned int duration , duration2 ;
 vpx_usec_timer_mark ( & tsctimer ) ;
 vpx_usec_timer_mark ( & ticktimer ) ;
 duration = ( int ) ( vpx_usec_timer_elapsed ( & ticktimer ) ) ;
 duration2 = ( unsigned int ) ( ( double ) duration / 2 ) ;
 if ( cm -> frame_type != KEY_FRAME ) {
 if ( cpi -> avg_encode_time == 0 ) cpi -> avg_encode_time = duration ;
 else cpi -> avg_encode_time = ( 7 * cpi -> avg_encode_time + duration ) >> 3 ;
 }
 if ( duration2 ) {
 {
 if ( cpi -> avg_pick_mode_time == 0 ) cpi -> avg_pick_mode_time = duration2 ;
 else cpi -> avg_pick_mode_time = ( 7 * cpi -> avg_pick_mode_time + duration2 ) >> 3 ;
 }
 }
 }
 if ( cm -> refresh_entropy_probs == 0 ) {
 vpx_memcpy ( & cm -> fc , & cm -> lfc , sizeof ( cm -> fc ) ) ;
 }
 if ( cm -> refresh_alt_ref_frame ) vpx_memcpy ( & cpi -> lfc_a , & cm -> fc , sizeof ( cm -> fc ) ) ;
 if ( cm -> refresh_golden_frame ) vpx_memcpy ( & cpi -> lfc_g , & cm -> fc , sizeof ( cm -> fc ) ) ;
 if ( cm -> refresh_last_frame ) vpx_memcpy ( & cpi -> lfc_n , & cm -> fc , sizeof ( cm -> fc ) ) ;
 if ( * size > 0 ) {
 cpi -> droppable = ! frame_is_reference ( cpi ) ;
 cm -> refresh_entropy_probs = 1 ;
 cm -> refresh_alt_ref_frame = 0 ;
 cm -> refresh_golden_frame = 0 ;
 cm -> refresh_last_frame = 1 ;
 cm -> frame_type = INTER_FRAME ;
 }
 if ( cpi -> oxcf . number_of_layers > 1 ) save_layer_context ( cpi ) ;
 vpx_usec_timer_mark ( & cmptimer ) ;
 cpi -> time_compress_data += vpx_usec_timer_elapsed ( & cmptimer ) ;
 if ( cpi -> b_calculate_psnr && cpi -> pass != 1 && cm -> show_frame ) {
 generate_psnr_packet ( cpi ) ;
 }

 cpi -> bytes += * size ;
 if ( cm -> show_frame ) {
 cpi -> common . show_frame_mi = cpi -> common . mi ;
 cpi -> count ++ ;
 if ( cpi -> b_calculate_psnr ) {
 uint64_t ye , ue , ve ;
 double frame_psnr ;
 YV12_BUFFER_CONFIG * orig = cpi -> Source ;
 YV12_BUFFER_CONFIG * recon = cpi -> common . frame_to_show ;
 int y_samples = orig -> y_height * orig -> y_width ;
 int uv_samples = orig -> uv_height * orig -> uv_width ;
 int t_samples = y_samples + 2 * uv_samples ;
 double sq_error ;
 ye = calc_plane_error ( orig -> y_buffer , orig -> y_stride , recon -> y_buffer , recon -> y_stride , orig -> y_width , orig -> y_height ) ;
 ue = calc_plane_error ( orig -> u_buffer , orig -> uv_stride , recon -> u_buffer , recon -> uv_stride , orig -> uv_width , orig -> uv_height ) ;
 ve = calc_plane_error ( orig -> v_buffer , orig -> uv_stride , recon -> v_buffer , recon -> uv_stride , orig -> uv_width , orig -> uv_height ) ;
 sq_error = ( double ) ( ye + ue + ve ) ;
 frame_psnr = vpx_sse_to_psnr ( t_samples , 255.0 , sq_error ) ;
 cpi -> total_y += vpx_sse_to_psnr ( y_samples , 255.0 , ( double ) ye ) ;
 cpi -> total_u += vpx_sse_to_psnr ( uv_samples , 255.0 , ( double ) ue ) ;
 cpi -> total_v += vpx_sse_to_psnr ( uv_samples , 255.0 , ( double ) ve ) ;
 cpi -> total_sq_error += sq_error ;
 cpi -> total += frame_psnr ;

 YV12_BUFFER_CONFIG * pp = & cm -> post_proc_buffer ;
 double sq_error2 ;
 double frame_psnr2 , frame_ssim2 = 0 ;
 double weight = 0 ;
 vp8_deblock ( cm , cm -> frame_to_show , & cm -> post_proc_buffer , cm -> filter_level * 10 / 6 , 1 , 0 ) ;
 vp8_clear_system_state ( ) ;
 ye = calc_plane_error ( orig -> y_buffer , orig -> y_stride , pp -> y_buffer , pp -> y_stride , orig -> y_width , orig -> y_height ) ;
 ue = calc_plane_error ( orig -> u_buffer , orig -> uv_stride , pp -> u_buffer , pp -> uv_stride , orig -> uv_width , orig -> uv_height ) ;
 ve = calc_plane_error ( orig -> v_buffer , orig -> uv_stride , pp -> v_buffer , pp -> uv_stride , orig -> uv_width , orig -> uv_height ) ;
 sq_error2 = ( double ) ( ye + ue + ve ) ;
 frame_psnr2 = vpx_sse_to_psnr ( t_samples , 255.0 , sq_error2 ) ;
 cpi -> totalp_y += vpx_sse_to_psnr ( y_samples , 255.0 , ( double ) ye ) ;
 cpi -> totalp_u += vpx_sse_to_psnr ( uv_samples , 255.0 , ( double ) ue ) ;
 cpi -> totalp_v += vpx_sse_to_psnr ( uv_samples , 255.0 , ( double ) ve ) ;
 cpi -> total_sq_error2 += sq_error2 ;
 cpi -> totalp += frame_psnr2 ;
 frame_ssim2 = vp8_calc_ssim ( cpi -> Source , & cm -> post_proc_buffer , 1 , & weight ) ;
 cpi -> summed_quality += frame_ssim2 * weight ;
 cpi -> summed_weights += weight ;
 if ( cpi -> oxcf . number_of_layers > 1 ) {
 unsigned int i ;
 for ( i = cpi -> current_layer ;
 i < cpi -> oxcf . number_of_layers ;
 i ++ ) {
 cpi -> frames_in_layer [ i ] ++ ;
 cpi -> bytes_in_layer [ i ] += * size ;
 cpi -> sum_psnr [ i ] += frame_psnr ;
 cpi -> sum_psnr_p [ i ] += frame_psnr2 ;
 cpi -> total_error2 [ i ] += sq_error ;
 cpi -> total_error2_p [ i ] += sq_error2 ;
 cpi -> sum_ssim [ i ] += frame_ssim2 * weight ;
 cpi -> sum_weights [ i ] += weight ;
 }
 }
 }

 if ( cpi -> b_calculate_ssimg ) {
 double y , u , v , frame_all ;
 frame_all = vp8_calc_ssimg ( cpi -> Source , cm -> frame_to_show , & y , & u , & v ) ;
 if ( cpi -> oxcf . number_of_layers > 1 ) {
 unsigned int i ;
 for ( i = cpi -> current_layer ;
 i < cpi -> oxcf . number_of_layers ;
 i ++ ) {
 if ( ! cpi -> b_calculate_psnr ) cpi -> frames_in_layer [ i ] ++ ;
 cpi -> total_ssimg_y_in_layer [ i ] += y ;
 cpi -> total_ssimg_u_in_layer [ i ] += u ;
 cpi -> total_ssimg_v_in_layer [ i ] += v ;
 cpi -> total_ssimg_all_in_layer [ i ] += frame_all ;
 }
 }
 else {
 cpi -> total_ssimg_y += y ;
 cpi -> total_ssimg_u += u ;
 cpi -> total_ssimg_v += v ;
 cpi -> total_ssimg_all += frame_all ;
 }
 }
 }
 }

 skiptruecount += cpi -> skip_true_count ;
 skipfalsecount += cpi -> skip_false_count ;
 }

 FILE * f = fopen ( "skip.stt" , "a" ) ;
 fprintf ( f , "frame:%4d flags:%4x Q:%4d P:%4d Size:%5d\n" , cpi -> common . current_video_frame , * frame_flags , cpi -> common . base_qindex , cpi -> prob_skip_false , * size ) ;
 if ( cpi -> is_src_frame_alt_ref == 1 ) fprintf ( f , "skipcount: %4d framesize: %d\n" , cpi -> skip_true_count , * size ) ;
 fclose ( f ) ;
 }

 return 0 ;
 }
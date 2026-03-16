struct VP8_COMP * vp8_create_compressor ( VP8_CONFIG * oxcf ) {
 int i ;
 VP8_COMP * cpi ;
 VP8_COMMON * cm ;
 cpi = vpx_memalign ( 32 , sizeof ( VP8_COMP ) ) ;
 if ( ! cpi ) return 0 ;
 cm = & cpi -> common ;
 vpx_memset ( cpi , 0 , sizeof ( VP8_COMP ) ) ;
 if ( setjmp ( cm -> error . jmp ) ) {
 cpi -> common . error . setjmp = 0 ;
 vp8_remove_compressor ( & cpi ) ;
 return 0 ;
 }
 cpi -> common . error . setjmp = 1 ;
 CHECK_MEM_ERROR ( cpi -> mb . ss , vpx_calloc ( sizeof ( search_site ) , ( MAX_MVSEARCH_STEPS * 8 ) + 1 ) ) ;
 vp8_create_common ( & cpi -> common ) ;
 init_config ( cpi , oxcf ) ;
 memcpy ( cpi -> base_skip_false_prob , vp8cx_base_skip_false_prob , sizeof ( vp8cx_base_skip_false_prob ) ) ;
 cpi -> common . current_video_frame = 0 ;
 cpi -> temporal_pattern_counter = 0 ;
 cpi -> kf_overspend_bits = 0 ;
 cpi -> kf_bitrate_adjustment = 0 ;
 cpi -> frames_till_gf_update_due = 0 ;
 cpi -> gf_overspend_bits = 0 ;
 cpi -> non_gf_bitrate_adjustment = 0 ;
 cpi -> prob_last_coded = 128 ;
 cpi -> prob_gf_coded = 128 ;
 cpi -> prob_intra_coded = 63 ;
 cpi -> recent_ref_frame_usage [ INTRA_FRAME ] = 1 ;
 cpi -> recent_ref_frame_usage [ LAST_FRAME ] = 1 ;
 cpi -> recent_ref_frame_usage [ GOLDEN_FRAME ] = 1 ;
 cpi -> recent_ref_frame_usage [ ALTREF_FRAME ] = 1 ;
 cpi -> common . ref_frame_sign_bias [ ALTREF_FRAME ] = 1 ;
 cpi -> twopass . gf_decay_rate = 0 ;
 cpi -> baseline_gf_interval = DEFAULT_GF_INTERVAL ;
 cpi -> gold_is_last = 0 ;
 cpi -> alt_is_last = 0 ;
 cpi -> gold_is_alt = 0 ;
 cpi -> active_map_enabled = 0 ;

 cpi -> one_pass_frame_index = 0 ;
 for ( i = 0 ;
 i < MAX_LAG_BUFFERS ;
 i ++ ) {
 cpi -> one_pass_frame_stats [ i ] . frames_so_far = 0 ;
 cpi -> one_pass_frame_stats [ i ] . frame_intra_error = 0.0 ;
 cpi -> one_pass_frame_stats [ i ] . frame_coded_error = 0.0 ;
 cpi -> one_pass_frame_stats [ i ] . frame_pcnt_inter = 0.0 ;
 cpi -> one_pass_frame_stats [ i ] . frame_pcnt_motion = 0.0 ;
 cpi -> one_pass_frame_stats [ i ] . frame_mvr = 0.0 ;
 cpi -> one_pass_frame_stats [ i ] . frame_mvr_abs = 0.0 ;
 cpi -> one_pass_frame_stats [ i ] . frame_mvc = 0.0 ;
 cpi -> one_pass_frame_stats [ i ] . frame_mvc_abs = 0.0 ;
 }
 }

 cpi -> cyclic_refresh_mode_max_mbs_perframe = ( cpi -> common . mb_rows * cpi -> common . mb_cols ) / 5 ;
 if ( cpi -> oxcf . number_of_layers == 1 ) {
 cpi -> cyclic_refresh_mode_max_mbs_perframe = ( cpi -> common . mb_rows * cpi -> common . mb_cols ) / 20 ;
 }
 else if ( cpi -> oxcf . number_of_layers == 2 ) {
 cpi -> cyclic_refresh_mode_max_mbs_perframe = ( cpi -> common . mb_rows * cpi -> common . mb_cols ) / 10 ;
 }
 cpi -> cyclic_refresh_mode_index = 0 ;
 cpi -> cyclic_refresh_q = 32 ;
 if ( cpi -> cyclic_refresh_mode_enabled ) {
 CHECK_MEM_ERROR ( cpi -> cyclic_refresh_map , vpx_calloc ( ( cpi -> common . mb_rows * cpi -> common . mb_cols ) , 1 ) ) ;
 }
 else cpi -> cyclic_refresh_map = ( signed char * ) NULL ;
 CHECK_MEM_ERROR ( cpi -> consec_zero_last , vpx_calloc ( cpi -> common . mb_rows * cpi -> common . mb_cols , 1 ) ) ;


 cpi -> frames_since_key = 8 ;
 cpi -> key_frame_frequency = cpi -> oxcf . key_freq ;
 cpi -> this_key_frame_forced = 0 ;
 cpi -> next_key_frame_forced = 0 ;
 cpi -> source_alt_ref_pending = 0 ;
 cpi -> source_alt_ref_active = 0 ;
 cpi -> common . refresh_alt_ref_frame = 0 ;
 cpi -> b_calculate_psnr = CONFIG_INTERNAL_STATS ;

 cpi -> count = 0 ;
 cpi -> bytes = 0 ;
 if ( cpi -> b_calculate_psnr ) {
 cpi -> total_sq_error = 0.0 ;
 cpi -> total_sq_error2 = 0.0 ;
 cpi -> total_y = 0.0 ;
 cpi -> total_u = 0.0 ;
 cpi -> total_v = 0.0 ;
 cpi -> total = 0.0 ;
 cpi -> totalp_y = 0.0 ;
 cpi -> totalp_u = 0.0 ;
 cpi -> totalp_v = 0.0 ;
 cpi -> totalp = 0.0 ;
 cpi -> tot_recode_hits = 0 ;
 cpi -> summed_quality = 0 ;
 cpi -> summed_weights = 0 ;
 }
 if ( cpi -> b_calculate_ssimg ) {
 cpi -> total_ssimg_y = 0 ;
 cpi -> total_ssimg_u = 0 ;
 cpi -> total_ssimg_v = 0 ;
 cpi -> total_ssimg_all = 0 ;
 }

 cpi -> frames_till_gf_update_due = 0 ;
 cpi -> key_frame_count = 1 ;
 cpi -> ni_av_qi = cpi -> oxcf . worst_allowed_q ;
 cpi -> ni_tot_qi = 0 ;
 cpi -> ni_frames = 0 ;
 cpi -> total_byte_count = 0 ;
 cpi -> drop_frame = 0 ;
 cpi -> rate_correction_factor = 1.0 ;
 cpi -> key_frame_rate_correction_factor = 1.0 ;
 cpi -> gf_rate_correction_factor = 1.0 ;
 cpi -> twopass . est_max_qcorrection_factor = 1.0 ;
 for ( i = 0 ;
 i < KEY_FRAME_CONTEXT ;
 i ++ ) {
 cpi -> prior_key_frame_distance [ i ] = ( int ) cpi -> output_framerate ;
 }



 kf_list = fopen ( "kf_list.stt" , "w" ) ;


 vp8_init_first_pass ( cpi ) ;
 }
 else if ( cpi -> pass == 2 ) {
 size_t packet_sz = sizeof ( FIRSTPASS_STATS ) ;
 int packets = ( int ) ( oxcf -> two_pass_stats_in . sz / packet_sz ) ;
 cpi -> twopass . stats_in_start = oxcf -> two_pass_stats_in . buf ;
 cpi -> twopass . stats_in = cpi -> twopass . stats_in_start ;
 cpi -> twopass . stats_in_end = ( void * ) ( ( char * ) cpi -> twopass . stats_in + ( packets - 1 ) * packet_sz ) ;
 vp8_init_second_pass ( cpi ) ;
 }

 cpi -> avg_encode_time = 0 ;
 cpi -> avg_pick_mode_time = 0 ;
 }
 vp8_set_speed_features ( cpi ) ;
 for ( i = 0 ;
 i < MAX_MODES ;
 i ++ ) {
 cpi -> mb . rd_thresh_mult [ i ] = 128 ;
 }


 vp8_remove_compressor ( & cpi ) ;
 return 0 ;
 }

 cpi -> fn_ptr [ BLOCK_16X16 ] . vf = vp8_variance16x16 ;
 cpi -> fn_ptr [ BLOCK_16X16 ] . svf = vp8_sub_pixel_variance16x16 ;
 cpi -> fn_ptr [ BLOCK_16X16 ] . svf_halfpix_h = vp8_variance_halfpixvar16x16_h ;
 cpi -> fn_ptr [ BLOCK_16X16 ] . svf_halfpix_v = vp8_variance_halfpixvar16x16_v ;
 cpi -> fn_ptr [ BLOCK_16X16 ] . svf_halfpix_hv = vp8_variance_halfpixvar16x16_hv ;
 cpi -> fn_ptr [ BLOCK_16X16 ] . sdx3f = vp8_sad16x16x3 ;
 cpi -> fn_ptr [ BLOCK_16X16 ] . sdx8f = vp8_sad16x16x8 ;
 cpi -> fn_ptr [ BLOCK_16X16 ] . sdx4df = vp8_sad16x16x4d ;
 cpi -> fn_ptr [ BLOCK_16X8 ] . sdf = vp8_sad16x8 ;
 cpi -> fn_ptr [ BLOCK_16X8 ] . vf = vp8_variance16x8 ;
 cpi -> fn_ptr [ BLOCK_16X8 ] . svf = vp8_sub_pixel_variance16x8 ;
 cpi -> fn_ptr [ BLOCK_16X8 ] . svf_halfpix_h = NULL ;
 cpi -> fn_ptr [ BLOCK_16X8 ] . svf_halfpix_v = NULL ;
 cpi -> fn_ptr [ BLOCK_16X8 ] . svf_halfpix_hv = NULL ;
 cpi -> fn_ptr [ BLOCK_16X8 ] . sdx3f = vp8_sad16x8x3 ;
 cpi -> fn_ptr [ BLOCK_16X8 ] . sdx8f = vp8_sad16x8x8 ;
 cpi -> fn_ptr [ BLOCK_16X8 ] . sdx4df = vp8_sad16x8x4d ;
 cpi -> fn_ptr [ BLOCK_8X16 ] . sdf = vp8_sad8x16 ;
 cpi -> fn_ptr [ BLOCK_8X16 ] . vf = vp8_variance8x16 ;
 cpi -> fn_ptr [ BLOCK_8X16 ] . svf = vp8_sub_pixel_variance8x16 ;
 cpi -> fn_ptr [ BLOCK_8X16 ] . svf_halfpix_h = NULL ;
 cpi -> fn_ptr [ BLOCK_8X16 ] . svf_halfpix_v = NULL ;
 cpi -> fn_ptr [ BLOCK_8X16 ] . svf_halfpix_hv = NULL ;
 cpi -> fn_ptr [ BLOCK_8X16 ] . sdx3f = vp8_sad8x16x3 ;
 cpi -> fn_ptr [ BLOCK_8X16 ] . sdx8f = vp8_sad8x16x8 ;
 cpi -> fn_ptr [ BLOCK_8X16 ] . sdx4df = vp8_sad8x16x4d ;
 cpi -> fn_ptr [ BLOCK_8X8 ] . sdf = vp8_sad8x8 ;
 cpi -> fn_ptr [ BLOCK_8X8 ] . vf = vp8_variance8x8 ;
 cpi -> fn_ptr [ BLOCK_8X8 ] . svf = vp8_sub_pixel_variance8x8 ;
 cpi -> fn_ptr [ BLOCK_8X8 ] . svf_halfpix_h = NULL ;
 cpi -> fn_ptr [ BLOCK_8X8 ] . svf_halfpix_v = NULL ;
 cpi -> fn_ptr [ BLOCK_8X8 ] . svf_halfpix_hv = NULL ;
 cpi -> fn_ptr [ BLOCK_8X8 ] . sdx3f = vp8_sad8x8x3 ;
 cpi -> fn_ptr [ BLOCK_8X8 ] . sdx8f = vp8_sad8x8x8 ;
 cpi -> fn_ptr [ BLOCK_8X8 ] . sdx4df = vp8_sad8x8x4d ;
 cpi -> fn_ptr [ BLOCK_4X4 ] . sdf = vp8_sad4x4 ;
 cpi -> fn_ptr [ BLOCK_4X4 ] . vf = vp8_variance4x4 ;
 cpi -> fn_ptr [ BLOCK_4X4 ] . svf = vp8_sub_pixel_variance4x4 ;
 cpi -> fn_ptr [ BLOCK_4X4 ] . svf_halfpix_h = NULL ;
 cpi -> fn_ptr [ BLOCK_4X4 ] . svf_halfpix_v = NULL ;
 cpi -> fn_ptr [ BLOCK_4X4 ] . svf_halfpix_hv = NULL ;
 cpi -> fn_ptr [ BLOCK_4X4 ] . sdx3f = vp8_sad4x4x3 ;
 cpi -> fn_ptr [ BLOCK_4X4 ] . sdx8f = vp8_sad4x4x8 ;
 cpi -> fn_ptr [ BLOCK_4X4 ] . sdx4df = vp8_sad4x4x4d ;

 cpi -> fn_ptr [ BLOCK_16X8 ] . copymem = vp8_copy32xn ;
 cpi -> fn_ptr [ BLOCK_8X16 ] . copymem = vp8_copy32xn ;
 cpi -> fn_ptr [ BLOCK_8X8 ] . copymem = vp8_copy32xn ;
 cpi -> fn_ptr [ BLOCK_4X4 ] . copymem = vp8_copy32xn ;

 cpi -> diamond_search_sad = vp8_diamond_search_sad ;
 cpi -> refining_search_sad = vp8_refining_search_sad ;
 cpi -> mb . error_bins [ 0 ] = cpi -> common . MBs ;
 vp8cx_init_quantizer ( cpi ) ;
 vp8_loop_filter_init ( cm ) ;
 cpi -> common . error . setjmp = 0 ;


 cpi -> mb . mvcost [ 1 ] = & cpi -> rd_costs . mvcosts [ 1 ] [ mv_max + 1 ] ;
 cpi -> mb . mvsadcost [ 0 ] = & cpi -> rd_costs . mvsadcosts [ 0 ] [ mvfp_max + 1 ] ;
 cpi -> mb . mvsadcost [ 1 ] = & cpi -> rd_costs . mvsadcosts [ 1 ] [ mvfp_max + 1 ] ;
 cal_mvsadcosts ( cpi -> mb . mvsadcost ) ;
 cpi -> mb . mbmode_cost = cpi -> rd_costs . mbmode_cost ;
 cpi -> mb . intra_uv_mode_cost = cpi -> rd_costs . intra_uv_mode_cost ;
 cpi -> mb . bmode_costs = cpi -> rd_costs . bmode_costs ;
 cpi -> mb . inter_bmode_costs = cpi -> rd_costs . inter_bmode_costs ;
 cpi -> mb . token_costs = cpi -> rd_costs . token_costs ;
 vp8_setup_block_ptrs ( & cpi -> mb ) ;
 vp8_setup_block_dptrs ( & cpi -> mb . e_mbd ) ;
 return cpi ;
 }
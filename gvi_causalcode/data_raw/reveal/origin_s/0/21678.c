VP9_COMP * vp9_create_compressor ( VP9EncoderConfig * oxcf ) {
 unsigned int i , j ;
 VP9_COMP * const cpi = vpx_memalign ( 32 , sizeof ( VP9_COMP ) ) ;
 VP9_COMMON * const cm = cpi != NULL ? & cpi -> common : NULL ;
 if ( ! cm ) return NULL ;
 vp9_zero ( * cpi ) ;
 if ( setjmp ( cm -> error . jmp ) ) {
 cm -> error . setjmp = 0 ;
 vp9_remove_compressor ( cpi ) ;
 return 0 ;
 }
 cm -> error . setjmp = 1 ;
 cpi -> use_svc = 0 ;
 init_config ( cpi , oxcf ) ;
 vp9_rc_init ( & cpi -> oxcf , oxcf -> pass , & cpi -> rc ) ;
 cm -> current_video_frame = 0 ;
 cpi -> skippable_frame = 0 ;
 CHECK_MEM_ERROR ( cm , cpi -> segmentation_map , vpx_calloc ( cm -> mi_rows * cm -> mi_cols , 1 ) ) ;
 CHECK_MEM_ERROR ( cm , cpi -> complexity_map , vpx_calloc ( cm -> mi_rows * cm -> mi_cols , 1 ) ) ;
 CHECK_MEM_ERROR ( cm , cpi -> cyclic_refresh , vp9_cyclic_refresh_alloc ( cm -> mi_rows , cm -> mi_cols ) ) ;
 CHECK_MEM_ERROR ( cm , cpi -> coding_context . last_frame_seg_map_copy , vpx_calloc ( cm -> mi_rows * cm -> mi_cols , 1 ) ) ;
 CHECK_MEM_ERROR ( cm , cpi -> nmvcosts [ 0 ] , vpx_calloc ( MV_VALS , sizeof ( * cpi -> nmvcosts [ 0 ] ) ) ) ;
 CHECK_MEM_ERROR ( cm , cpi -> nmvcosts [ 1 ] , vpx_calloc ( MV_VALS , sizeof ( * cpi -> nmvcosts [ 1 ] ) ) ) ;
 CHECK_MEM_ERROR ( cm , cpi -> nmvcosts_hp [ 0 ] , vpx_calloc ( MV_VALS , sizeof ( * cpi -> nmvcosts_hp [ 0 ] ) ) ) ;
 CHECK_MEM_ERROR ( cm , cpi -> nmvcosts_hp [ 1 ] , vpx_calloc ( MV_VALS , sizeof ( * cpi -> nmvcosts_hp [ 1 ] ) ) ) ;
 CHECK_MEM_ERROR ( cm , cpi -> nmvsadcosts [ 0 ] , vpx_calloc ( MV_VALS , sizeof ( * cpi -> nmvsadcosts [ 0 ] ) ) ) ;
 CHECK_MEM_ERROR ( cm , cpi -> nmvsadcosts [ 1 ] , vpx_calloc ( MV_VALS , sizeof ( * cpi -> nmvsadcosts [ 1 ] ) ) ) ;
 CHECK_MEM_ERROR ( cm , cpi -> nmvsadcosts_hp [ 0 ] , vpx_calloc ( MV_VALS , sizeof ( * cpi -> nmvsadcosts_hp [ 0 ] ) ) ) ;
 CHECK_MEM_ERROR ( cm , cpi -> nmvsadcosts_hp [ 1 ] , vpx_calloc ( MV_VALS , sizeof ( * cpi -> nmvsadcosts_hp [ 1 ] ) ) ) ;
 for ( i = 0 ;
 i < ( sizeof ( cpi -> mbgraph_stats ) / sizeof ( cpi -> mbgraph_stats [ 0 ] ) ) ;
 i ++ ) {
 CHECK_MEM_ERROR ( cm , cpi -> mbgraph_stats [ i ] . mb_stats , vpx_calloc ( cm -> MBs * sizeof ( * cpi -> mbgraph_stats [ i ] . mb_stats ) , 1 ) ) ;
 }

 if ( cpi -> use_fp_mb_stats ) {
 CHECK_MEM_ERROR ( cm , cpi -> twopass . frame_mb_stats_buf , vpx_calloc ( cm -> MBs * sizeof ( uint8_t ) , 1 ) ) ;
 }
 else {
 cpi -> twopass . frame_mb_stats_buf = NULL ;
 }

 cpi -> multi_arf_last_grp_enabled = 0 ;
 if ( oxcf -> pass == 2 ) {
 if ( cpi -> use_svc ) {
 cpi -> multi_arf_allowed = 0 ;
 cpi -> multi_arf_enabled = 0 ;
 }
 else {
 cpi -> multi_arf_allowed = 0 ;
 cpi -> multi_arf_enabled = 0 ;
 }
 }
 else {
 cpi -> multi_arf_allowed = 0 ;
 cpi -> multi_arf_enabled = 0 ;
 }
 cpi -> b_calculate_psnr = CONFIG_INTERNAL_STATS ;

 cpi -> count = 0 ;
 cpi -> bytes = 0 ;
 if ( cpi -> b_calculate_psnr ) {
 cpi -> total_y = 0.0 ;
 cpi -> total_u = 0.0 ;
 cpi -> total_v = 0.0 ;
 cpi -> total = 0.0 ;
 cpi -> total_sq_error = 0 ;
 cpi -> total_samples = 0 ;
 cpi -> totalp_y = 0.0 ;
 cpi -> totalp_u = 0.0 ;
 cpi -> totalp_v = 0.0 ;
 cpi -> totalp = 0.0 ;
 cpi -> totalp_sq_error = 0 ;
 cpi -> totalp_samples = 0 ;
 cpi -> tot_recode_hits = 0 ;
 cpi -> summed_quality = 0 ;
 cpi -> summed_weights = 0 ;
 cpi -> summedp_quality = 0 ;
 cpi -> summedp_weights = 0 ;
 }
 if ( cpi -> b_calculate_ssimg ) {
 cpi -> total_ssimg_y = 0 ;
 cpi -> total_ssimg_u = 0 ;
 cpi -> total_ssimg_v = 0 ;
 cpi -> total_ssimg_all = 0 ;
 }

 cal_nmvjointsadcost ( cpi -> mb . nmvjointsadcost ) ;
 cpi -> mb . nmvcost [ 0 ] = & cpi -> nmvcosts [ 0 ] [ MV_MAX ] ;
 cpi -> mb . nmvcost [ 1 ] = & cpi -> nmvcosts [ 1 ] [ MV_MAX ] ;
 cpi -> mb . nmvsadcost [ 0 ] = & cpi -> nmvsadcosts [ 0 ] [ MV_MAX ] ;
 cpi -> mb . nmvsadcost [ 1 ] = & cpi -> nmvsadcosts [ 1 ] [ MV_MAX ] ;
 cal_nmvsadcosts ( cpi -> mb . nmvsadcost ) ;
 cpi -> mb . nmvcost_hp [ 0 ] = & cpi -> nmvcosts_hp [ 0 ] [ MV_MAX ] ;
 cpi -> mb . nmvcost_hp [ 1 ] = & cpi -> nmvcosts_hp [ 1 ] [ MV_MAX ] ;
 cpi -> mb . nmvsadcost_hp [ 0 ] = & cpi -> nmvsadcosts_hp [ 0 ] [ MV_MAX ] ;
 cpi -> mb . nmvsadcost_hp [ 1 ] = & cpi -> nmvsadcosts_hp [ 1 ] [ MV_MAX ] ;
 cal_nmvsadcosts_hp ( cpi -> mb . nmvsadcost_hp ) ;



 kf_list = fopen ( "kf_list.stt" , "w" ) ;

 if ( oxcf -> pass == 1 ) {
 vp9_init_first_pass ( cpi ) ;
 }
 else if ( oxcf -> pass == 2 ) {
 const size_t packet_sz = sizeof ( FIRSTPASS_STATS ) ;
 const int packets = ( int ) ( oxcf -> two_pass_stats_in . sz / packet_sz ) ;
 if ( cpi -> svc . number_spatial_layers > 1 || cpi -> svc . number_temporal_layers > 1 ) {
 FIRSTPASS_STATS * const stats = oxcf -> two_pass_stats_in . buf ;
 FIRSTPASS_STATS * stats_copy [ VPX_SS_MAX_LAYERS ] = {
 0 }
 ;
 int i ;
 for ( i = 0 ;
 i < oxcf -> ss_number_layers ;
 ++ i ) {
 FIRSTPASS_STATS * const last_packet_for_layer = & stats [ packets - oxcf -> ss_number_layers + i ] ;
 const int layer_id = ( int ) last_packet_for_layer -> spatial_layer_id ;
 const int packets_in_layer = ( int ) last_packet_for_layer -> count + 1 ;
 if ( layer_id >= 0 && layer_id < oxcf -> ss_number_layers ) {
 LAYER_CONTEXT * const lc = & cpi -> svc . layer_context [ layer_id ] ;
 vpx_free ( lc -> rc_twopass_stats_in . buf ) ;
 lc -> rc_twopass_stats_in . sz = packets_in_layer * packet_sz ;
 CHECK_MEM_ERROR ( cm , lc -> rc_twopass_stats_in . buf , vpx_malloc ( lc -> rc_twopass_stats_in . sz ) ) ;
 lc -> twopass . stats_in_start = lc -> rc_twopass_stats_in . buf ;
 lc -> twopass . stats_in = lc -> twopass . stats_in_start ;
 lc -> twopass . stats_in_end = lc -> twopass . stats_in_start + packets_in_layer - 1 ;
 stats_copy [ layer_id ] = lc -> rc_twopass_stats_in . buf ;
 }
 }
 for ( i = 0 ;
 i < packets ;
 ++ i ) {
 const int layer_id = ( int ) stats [ i ] . spatial_layer_id ;
 if ( layer_id >= 0 && layer_id < oxcf -> ss_number_layers && stats_copy [ layer_id ] != NULL ) {
 * stats_copy [ layer_id ] = stats [ i ] ;
 ++ stats_copy [ layer_id ] ;
 }
 }
 vp9_init_second_pass_spatial_svc ( cpi ) ;
 }
 else {

 const size_t psz = cpi -> common . MBs * sizeof ( uint8_t ) ;
 const int ps = ( int ) ( oxcf -> firstpass_mb_stats_in . sz / psz ) ;
 cpi -> twopass . firstpass_mb_stats . mb_stats_start = oxcf -> firstpass_mb_stats_in . buf ;
 cpi -> twopass . firstpass_mb_stats . mb_stats_end = cpi -> twopass . firstpass_mb_stats . mb_stats_start + ( ps - 1 ) * cpi -> common . MBs * sizeof ( uint8_t ) ;
 }

 cpi -> twopass . stats_in = cpi -> twopass . stats_in_start ;
 cpi -> twopass . stats_in_end = & cpi -> twopass . stats_in [ packets - 1 ] ;
 vp9_init_second_pass ( cpi ) ;
 }
 }
 vp9_set_speed_features ( cpi ) ;
 CHECK_MEM_ERROR ( cm , cpi -> source_diff_var , vpx_calloc ( cm -> MBs , sizeof ( diff ) ) ) ;
 cpi -> source_var_thresh = 0 ;
 cpi -> frames_till_next_var_check = 0 ;
 for ( i = 0 ;
 i < BLOCK_SIZES ;
 ++ i ) {
 for ( j = 0 ;
 j < MAX_MODES ;
 ++ j ) {
 cpi -> rd . thresh_freq_fact [ i ] [ j ] = 32 ;
 cpi -> rd . mode_map [ i ] [ j ] = j ;
 }
 }

 cpi -> fn_ptr [ BT ] . sdaf = SDAF ;
 cpi -> fn_ptr [ BT ] . vf = VF ;
 cpi -> fn_ptr [ BT ] . svf = SVF ;
 cpi -> fn_ptr [ BT ] . svaf = SVAF ;
 cpi -> fn_ptr [ BT ] . sdx3f = SDX3F ;
 cpi -> fn_ptr [ BT ] . sdx8f = SDX8F ;
 cpi -> fn_ptr [ BT ] . sdx4df = SDX4DF ;
 BFP ( BLOCK_32X16 , vp9_sad32x16 , vp9_sad32x16_avg , vp9_variance32x16 , vp9_sub_pixel_variance32x16 , vp9_sub_pixel_avg_variance32x16 , NULL , NULL , vp9_sad32x16x4d ) BFP ( BLOCK_16X32 , vp9_sad16x32 , vp9_sad16x32_avg , vp9_variance16x32 , vp9_sub_pixel_variance16x32 , vp9_sub_pixel_avg_variance16x32 , NULL , NULL , vp9_sad16x32x4d ) BFP ( BLOCK_64X32 , vp9_sad64x32 , vp9_sad64x32_avg , vp9_variance64x32 , vp9_sub_pixel_variance64x32 , vp9_sub_pixel_avg_variance64x32 , NULL , NULL , vp9_sad64x32x4d ) BFP ( BLOCK_32X64 , vp9_sad32x64 , vp9_sad32x64_avg , vp9_variance32x64 , vp9_sub_pixel_variance32x64 , vp9_sub_pixel_avg_variance32x64 , NULL , NULL , vp9_sad32x64x4d ) BFP ( BLOCK_32X32 , vp9_sad32x32 , vp9_sad32x32_avg , vp9_variance32x32 , vp9_sub_pixel_variance32x32 , vp9_sub_pixel_avg_variance32x32 , vp9_sad32x32x3 , vp9_sad32x32x8 , vp9_sad32x32x4d ) BFP ( BLOCK_64X64 , vp9_sad64x64 , vp9_sad64x64_avg , vp9_variance64x64 , vp9_sub_pixel_variance64x64 , vp9_sub_pixel_avg_variance64x64 , vp9_sad64x64x3 , vp9_sad64x64x8 , vp9_sad64x64x4d ) BFP ( BLOCK_16X16 , vp9_sad16x16 , vp9_sad16x16_avg , vp9_variance16x16 , vp9_sub_pixel_variance16x16 , vp9_sub_pixel_avg_variance16x16 , vp9_sad16x16x3 , vp9_sad16x16x8 , vp9_sad16x16x4d ) BFP ( BLOCK_16X8 , vp9_sad16x8 , vp9_sad16x8_avg , vp9_variance16x8 , vp9_sub_pixel_variance16x8 , vp9_sub_pixel_avg_variance16x8 , vp9_sad16x8x3 , vp9_sad16x8x8 , vp9_sad16x8x4d ) BFP ( BLOCK_8X16 , vp9_sad8x16 , vp9_sad8x16_avg , vp9_variance8x16 , vp9_sub_pixel_variance8x16 , vp9_sub_pixel_avg_variance8x16 , vp9_sad8x16x3 , vp9_sad8x16x8 , vp9_sad8x16x4d ) BFP ( BLOCK_8X8 , vp9_sad8x8 , vp9_sad8x8_avg , vp9_variance8x8 , vp9_sub_pixel_variance8x8 , vp9_sub_pixel_avg_variance8x8 , vp9_sad8x8x3 , vp9_sad8x8x8 , vp9_sad8x8x4d ) BFP ( BLOCK_8X4 , vp9_sad8x4 , vp9_sad8x4_avg , vp9_variance8x4 , vp9_sub_pixel_variance8x4 , vp9_sub_pixel_avg_variance8x4 , NULL , vp9_sad8x4x8 , vp9_sad8x4x4d ) BFP ( BLOCK_4X8 , vp9_sad4x8 , vp9_sad4x8_avg , vp9_variance4x8 , vp9_sub_pixel_variance4x8 , vp9_sub_pixel_avg_variance4x8 , NULL , vp9_sad4x8x8 , vp9_sad4x8x4d ) BFP ( BLOCK_4X4 , vp9_sad4x4 , vp9_sad4x4_avg , vp9_variance4x4 , vp9_sub_pixel_variance4x4 , vp9_sub_pixel_avg_variance4x4 , vp9_sad4x4x3 , vp9_sad4x4x8 , vp9_sad4x4x4d ) vp9_init_quantizer ( cpi ) ;
 vp9_loop_filter_init ( cm ) ;
 cm -> error . setjmp = 0 ;
 return cpi ;
 }
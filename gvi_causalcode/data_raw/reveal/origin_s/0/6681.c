void vp9_first_pass ( VP9_COMP * cpi , const struct lookahead_entry * source ) {
 int mb_row , mb_col ;
 MACROBLOCK * const x = & cpi -> mb ;
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 TileInfo tile ;
 struct macroblock_plane * const p = x -> plane ;
 struct macroblockd_plane * const pd = xd -> plane ;
 const PICK_MODE_CONTEXT * ctx = & cpi -> pc_root -> none ;
 int i ;
 int recon_yoffset , recon_uvoffset ;
 YV12_BUFFER_CONFIG * const lst_yv12 = get_ref_frame_buffer ( cpi , LAST_FRAME ) ;
 YV12_BUFFER_CONFIG * gld_yv12 = get_ref_frame_buffer ( cpi , GOLDEN_FRAME ) ;
 YV12_BUFFER_CONFIG * const new_yv12 = get_frame_new_buffer ( cm ) ;
 int recon_y_stride = lst_yv12 -> y_stride ;
 int recon_uv_stride = lst_yv12 -> uv_stride ;
 int uv_mb_height = 16 >> ( lst_yv12 -> y_height > lst_yv12 -> uv_height ) ;
 int64_t intra_error = 0 ;
 int64_t coded_error = 0 ;
 int64_t sr_coded_error = 0 ;
 int sum_mvr = 0 , sum_mvc = 0 ;
 int sum_mvr_abs = 0 , sum_mvc_abs = 0 ;
 int64_t sum_mvrs = 0 , sum_mvcs = 0 ;
 int mvcount = 0 ;
 int intercount = 0 ;
 int second_ref_count = 0 ;
 const int intrapenalty = INTRA_MODE_PENALTY ;
 int neutral_count = 0 ;
 int new_mv_count = 0 ;
 int sum_in_vectors = 0 ;
 MV lastmv = {
 0 , 0 }
 ;
 TWO_PASS * twopass = & cpi -> twopass ;
 const MV zero_mv = {
 0 , 0 }
 ;
 const YV12_BUFFER_CONFIG * first_ref_buf = lst_yv12 ;
 LAYER_CONTEXT * const lc = is_two_pass_svc ( cpi ) ? & cpi -> svc . layer_context [ cpi -> svc . spatial_layer_id ] : NULL ;

 vp9_zero_array ( cpi -> twopass . frame_mb_stats_buf , cm -> MBs ) ;
 }

 set_first_pass_params ( cpi ) ;
 vp9_set_quantizer ( cm , find_fp_qindex ( cm -> bit_depth ) ) ;
 if ( lc != NULL ) {
 twopass = & lc -> twopass ;
 cpi -> lst_fb_idx = cpi -> svc . spatial_layer_id ;
 cpi -> ref_frame_flags = VP9_LAST_FLAG ;
 if ( cpi -> svc . number_spatial_layers + cpi -> svc . spatial_layer_id < REF_FRAMES ) {
 cpi -> gld_fb_idx = cpi -> svc . number_spatial_layers + cpi -> svc . spatial_layer_id ;
 cpi -> ref_frame_flags |= VP9_GOLD_FLAG ;
 cpi -> refresh_golden_frame = ( lc -> current_video_frame_in_layer == 0 ) ;
 }
 else {
 cpi -> refresh_golden_frame = 0 ;
 }
 if ( lc -> current_video_frame_in_layer == 0 ) cpi -> ref_frame_flags = 0 ;
 vp9_scale_references ( cpi ) ;
 if ( cpi -> ref_frame_flags & VP9_LAST_FLAG ) {
 first_ref_buf = vp9_get_scaled_ref_frame ( cpi , LAST_FRAME ) ;
 if ( first_ref_buf == NULL ) first_ref_buf = get_ref_frame_buffer ( cpi , LAST_FRAME ) ;
 }
 if ( cpi -> ref_frame_flags & VP9_GOLD_FLAG ) {
 const int ref_idx = cm -> ref_frame_map [ get_ref_frame_idx ( cpi , GOLDEN_FRAME ) ] ;
 const int scaled_idx = cpi -> scaled_ref_idx [ GOLDEN_FRAME - 1 ] ;
 gld_yv12 = ( scaled_idx != ref_idx ) ? & cm -> frame_bufs [ scaled_idx ] . buf : get_ref_frame_buffer ( cpi , GOLDEN_FRAME ) ;
 }
 else {
 gld_yv12 = NULL ;
 }
 recon_y_stride = new_yv12 -> y_stride ;
 recon_uv_stride = new_yv12 -> uv_stride ;
 uv_mb_height = 16 >> ( new_yv12 -> y_height > new_yv12 -> uv_height ) ;
 set_ref_ptrs ( cm , xd , ( cpi -> ref_frame_flags & VP9_LAST_FLAG ) ? LAST_FRAME : NONE , ( cpi -> ref_frame_flags & VP9_GOLD_FLAG ) ? GOLDEN_FRAME : NONE ) ;
 cpi -> Source = vp9_scale_if_required ( cm , cpi -> un_scaled_source , & cpi -> scaled_source ) ;
 }
 vp9_setup_block_planes ( & x -> e_mbd , cm -> subsampling_x , cm -> subsampling_y ) ;
 vp9_setup_src_planes ( x , cpi -> Source , 0 , 0 ) ;
 vp9_setup_pre_planes ( xd , 0 , first_ref_buf , 0 , 0 , NULL ) ;
 vp9_setup_dst_planes ( xd -> plane , new_yv12 , 0 , 0 ) ;
 xd -> mi = cm -> mi ;
 xd -> mi [ 0 ] . src_mi = & xd -> mi [ 0 ] ;
 vp9_frame_init_quantizer ( cpi ) ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 ++ i ) {
 p [ i ] . coeff = ctx -> coeff_pbuf [ i ] [ 1 ] ;
 p [ i ] . qcoeff = ctx -> qcoeff_pbuf [ i ] [ 1 ] ;
 pd [ i ] . dqcoeff = ctx -> dqcoeff_pbuf [ i ] [ 1 ] ;
 p [ i ] . eobs = ctx -> eobs_pbuf [ i ] [ 1 ] ;
 }
 x -> skip_recode = 0 ;
 vp9_init_mv_probs ( cm ) ;
 vp9_initialize_rd_consts ( cpi ) ;
 vp9_tile_init ( & tile , cm , 0 , 0 ) ;
 for ( mb_row = 0 ;
 mb_row < cm -> mb_rows ;
 ++ mb_row ) {
 MV best_ref_mv = {
 0 , 0 }
 ;
 xd -> up_available = ( mb_row != 0 ) ;
 recon_yoffset = ( mb_row * recon_y_stride * 16 ) ;
 recon_uvoffset = ( mb_row * recon_uv_stride * uv_mb_height ) ;
 x -> mv_row_min = - ( ( mb_row * 16 ) + BORDER_MV_PIXELS_B16 ) ;
 x -> mv_row_max = ( ( cm -> mb_rows - 1 - mb_row ) * 16 ) + BORDER_MV_PIXELS_B16 ;
 for ( mb_col = 0 ;
 mb_col < cm -> mb_cols ;
 ++ mb_col ) {
 int this_error ;
 const int use_dc_pred = ( mb_col || mb_row ) && ( ! mb_col || ! mb_row ) ;
 double error_weight = 1.0 ;
 const BLOCK_SIZE bsize = get_bsize ( cm , mb_row , mb_col ) ;


 xd -> plane [ 0 ] . dst . buf = new_yv12 -> y_buffer + recon_yoffset ;
 xd -> plane [ 1 ] . dst . buf = new_yv12 -> u_buffer + recon_uvoffset ;
 xd -> plane [ 2 ] . dst . buf = new_yv12 -> v_buffer + recon_uvoffset ;
 xd -> left_available = ( mb_col != 0 ) ;
 xd -> mi [ 0 ] . src_mi -> mbmi . sb_type = bsize ;
 xd -> mi [ 0 ] . src_mi -> mbmi . ref_frame [ 0 ] = INTRA_FRAME ;
 set_mi_row_col ( xd , & tile , mb_row << 1 , num_8x8_blocks_high_lookup [ bsize ] , mb_col << 1 , num_8x8_blocks_wide_lookup [ bsize ] , cm -> mi_rows , cm -> mi_cols ) ;
 if ( cpi -> oxcf . aq_mode == VARIANCE_AQ ) {
 const int energy = vp9_block_energy ( cpi , x , bsize ) ;
 error_weight = vp9_vaq_inv_q_ratio ( energy ) ;
 }
 x -> skip_encode = 0 ;
 xd -> mi [ 0 ] . src_mi -> mbmi . mode = DC_PRED ;
 xd -> mi [ 0 ] . src_mi -> mbmi . tx_size = use_dc_pred ? ( bsize >= BLOCK_16X16 ? TX_16X16 : TX_8X8 ) : TX_4X4 ;
 vp9_encode_intra_block_plane ( x , bsize , 0 ) ;
 this_error = vp9_get_mb_ss ( x -> plane [ 0 ] . src_diff ) ;
 if ( cpi -> oxcf . aq_mode == VARIANCE_AQ ) {
 vp9_clear_system_state ( ) ;
 this_error = ( int ) ( this_error * error_weight ) ;
 }
 this_error += intrapenalty ;
 intra_error += ( int64_t ) this_error ;

 cpi -> twopass . frame_mb_stats_buf [ mb_index ] = 0 ;
 }

 x -> mv_col_max = ( ( cm -> mb_cols - 1 - mb_col ) * 16 ) + BORDER_MV_PIXELS_B16 ;
 if ( ( lc == NULL && cm -> current_video_frame > 0 ) || ( lc != NULL && lc -> current_video_frame_in_layer > 0 ) ) {
 int tmp_err , motion_error , raw_motion_error ;
 MV mv = {
 0 , 0 }
 , tmp_mv = {
 0 , 0 }
 ;
 struct buf_2d unscaled_last_source_buf_2d ;
 xd -> plane [ 0 ] . pre [ 0 ] . buf = first_ref_buf -> y_buffer + recon_yoffset ;
 motion_error = get_prediction_error ( bsize , & x -> plane [ 0 ] . src , & xd -> plane [ 0 ] . pre [ 0 ] ) ;
 unscaled_last_source_buf_2d . buf = cpi -> unscaled_last_source -> y_buffer + recon_yoffset ;
 unscaled_last_source_buf_2d . stride = cpi -> unscaled_last_source -> y_stride ;
 raw_motion_error = get_prediction_error ( bsize , & x -> plane [ 0 ] . src , & unscaled_last_source_buf_2d ) ;
 if ( raw_motion_error > 25 || lc != NULL ) {
 first_pass_motion_search ( cpi , x , & best_ref_mv , & mv , & motion_error ) ;
 if ( cpi -> oxcf . aq_mode == VARIANCE_AQ ) {
 vp9_clear_system_state ( ) ;
 motion_error = ( int ) ( motion_error * error_weight ) ;
 }
 if ( ! is_zero_mv ( & best_ref_mv ) ) {
 tmp_err = INT_MAX ;
 first_pass_motion_search ( cpi , x , & zero_mv , & tmp_mv , & tmp_err ) ;
 if ( cpi -> oxcf . aq_mode == VARIANCE_AQ ) {
 vp9_clear_system_state ( ) ;
 tmp_err = ( int ) ( tmp_err * error_weight ) ;
 }
 if ( tmp_err < motion_error ) {
 motion_error = tmp_err ;
 mv = tmp_mv ;
 }
 }
 if ( ( ( lc == NULL && cm -> current_video_frame > 1 ) || ( lc != NULL && lc -> current_video_frame_in_layer > 1 ) ) && gld_yv12 != NULL ) {
 int gf_motion_error ;
 xd -> plane [ 0 ] . pre [ 0 ] . buf = gld_yv12 -> y_buffer + recon_yoffset ;
 gf_motion_error = get_prediction_error ( bsize , & x -> plane [ 0 ] . src , & xd -> plane [ 0 ] . pre [ 0 ] ) ;
 first_pass_motion_search ( cpi , x , & zero_mv , & tmp_mv , & gf_motion_error ) ;
 if ( cpi -> oxcf . aq_mode == VARIANCE_AQ ) {
 vp9_clear_system_state ( ) ;
 gf_motion_error = ( int ) ( gf_motion_error * error_weight ) ;
 }
 if ( gf_motion_error < motion_error && gf_motion_error < this_error ) ++ second_ref_count ;
 xd -> plane [ 0 ] . pre [ 0 ] . buf = first_ref_buf -> y_buffer + recon_yoffset ;
 xd -> plane [ 1 ] . pre [ 0 ] . buf = first_ref_buf -> u_buffer + recon_uvoffset ;
 xd -> plane [ 2 ] . pre [ 0 ] . buf = first_ref_buf -> v_buffer + recon_uvoffset ;
 if ( gf_motion_error < this_error ) sr_coded_error += gf_motion_error ;
 else sr_coded_error += this_error ;
 }
 else {
 sr_coded_error += motion_error ;
 }
 }
 else {
 sr_coded_error += motion_error ;
 }
 best_ref_mv . row = 0 ;
 best_ref_mv . col = 0 ;

 cpi -> twopass . frame_mb_stats_buf [ mb_index ] = 0 ;
 cpi -> twopass . frame_mb_stats_buf [ mb_index ] |= FPMB_DCINTRA_MASK ;
 cpi -> twopass . frame_mb_stats_buf [ mb_index ] |= FPMB_MOTION_ZERO_MASK ;
 if ( this_error > FPMB_ERROR_LARGE_TH ) {
 cpi -> twopass . frame_mb_stats_buf [ mb_index ] |= FPMB_ERROR_LARGE_MASK ;
 }
 else if ( this_error < FPMB_ERROR_SMALL_TH ) {
 cpi -> twopass . frame_mb_stats_buf [ mb_index ] |= FPMB_ERROR_SMALL_MASK ;
 }
 }

 if ( ( ( this_error - intrapenalty ) * 9 <= motion_error * 10 ) && this_error < 2 * intrapenalty ) ++ neutral_count ;
 mv . row *= 8 ;
 mv . col *= 8 ;
 this_error = motion_error ;
 xd -> mi [ 0 ] . src_mi -> mbmi . mode = NEWMV ;
 xd -> mi [ 0 ] . src_mi -> mbmi . mv [ 0 ] . as_mv = mv ;
 xd -> mi [ 0 ] . src_mi -> mbmi . tx_size = TX_4X4 ;
 xd -> mi [ 0 ] . src_mi -> mbmi . ref_frame [ 0 ] = LAST_FRAME ;
 xd -> mi [ 0 ] . src_mi -> mbmi . ref_frame [ 1 ] = NONE ;
 vp9_build_inter_predictors_sby ( xd , mb_row << 1 , mb_col << 1 , bsize ) ;
 vp9_encode_sby_pass1 ( x , bsize ) ;
 sum_mvr += mv . row ;
 sum_mvr_abs += abs ( mv . row ) ;
 sum_mvc += mv . col ;
 sum_mvc_abs += abs ( mv . col ) ;
 sum_mvrs += mv . row * mv . row ;
 sum_mvcs += mv . col * mv . col ;
 ++ intercount ;
 best_ref_mv = mv ;

 cpi -> twopass . frame_mb_stats_buf [ mb_index ] = 0 ;
 cpi -> twopass . frame_mb_stats_buf [ mb_index ] &= ~ FPMB_DCINTRA_MASK ;
 cpi -> twopass . frame_mb_stats_buf [ mb_index ] |= FPMB_MOTION_ZERO_MASK ;
 if ( this_error > FPMB_ERROR_LARGE_TH ) {
 cpi -> twopass . frame_mb_stats_buf [ mb_index ] |= FPMB_ERROR_LARGE_MASK ;
 }
 else if ( this_error < FPMB_ERROR_SMALL_TH ) {
 cpi -> twopass . frame_mb_stats_buf [ mb_index ] |= FPMB_ERROR_SMALL_MASK ;
 }
 }

 ++ mvcount ;

 cpi -> twopass . frame_mb_stats_buf [ mb_index ] &= ~ FPMB_MOTION_ZERO_MASK ;
 if ( mv . as_mv . col > 0 && mv . as_mv . col >= abs ( mv . as_mv . row ) ) {
 cpi -> twopass . frame_mb_stats_buf [ mb_index ] |= FPMB_MOTION_RIGHT_MASK ;
 }
 else if ( mv . as_mv . row < 0 && abs ( mv . as_mv . row ) >= abs ( mv . as_mv . col ) ) {
 cpi -> twopass . frame_mb_stats_buf [ mb_index ] |= FPMB_MOTION_UP_MASK ;
 }
 else if ( mv . as_mv . col < 0 && abs ( mv . as_mv . col ) >= abs ( mv . as_mv . row ) ) {
 cpi -> twopass . frame_mb_stats_buf [ mb_index ] |= FPMB_MOTION_LEFT_MASK ;
 }
 else {
 cpi -> twopass . frame_mb_stats_buf [ mb_index ] |= FPMB_MOTION_DOWN_MASK ;
 }
 }

 lastmv = mv ;
 if ( mb_row < cm -> mb_rows / 2 ) {
 if ( mv . row > 0 ) -- sum_in_vectors ;
 else if ( mv . row < 0 ) ++ sum_in_vectors ;
 }
 else if ( mb_row > cm -> mb_rows / 2 ) {
 if ( mv . row > 0 ) ++ sum_in_vectors ;
 else if ( mv . row < 0 ) -- sum_in_vectors ;
 }
 if ( mb_col < cm -> mb_cols / 2 ) {
 if ( mv . col > 0 ) -- sum_in_vectors ;
 else if ( mv . col < 0 ) ++ sum_in_vectors ;
 }
 else if ( mb_col > cm -> mb_cols / 2 ) {
 if ( mv . col > 0 ) ++ sum_in_vectors ;
 else if ( mv . col < 0 ) -- sum_in_vectors ;
 }
 }
 }
 }
 else {
 sr_coded_error += ( int64_t ) this_error ;
 }
 coded_error += ( int64_t ) this_error ;
 x -> plane [ 0 ] . src . buf += 16 ;
 x -> plane [ 1 ] . src . buf += uv_mb_height ;
 x -> plane [ 2 ] . src . buf += uv_mb_height ;
 recon_yoffset += 16 ;
 recon_uvoffset += uv_mb_height ;
 }
 x -> plane [ 0 ] . src . buf += 16 * x -> plane [ 0 ] . src . stride - 16 * cm -> mb_cols ;
 x -> plane [ 1 ] . src . buf += uv_mb_height * x -> plane [ 1 ] . src . stride - uv_mb_height * cm -> mb_cols ;
 x -> plane [ 2 ] . src . buf += uv_mb_height * x -> plane [ 1 ] . src . stride - uv_mb_height * cm -> mb_cols ;
 vp9_clear_system_state ( ) ;
 }
 vp9_clear_system_state ( ) ;
 {
 FIRSTPASS_STATS fps ;
 const double min_err = 200 * sqrt ( cm -> MBs ) ;
 fps . frame = cm -> current_video_frame ;
 fps . spatial_layer_id = cpi -> svc . spatial_layer_id ;
 fps . coded_error = ( double ) ( coded_error >> 8 ) + min_err ;
 fps . sr_coded_error = ( double ) ( sr_coded_error >> 8 ) + min_err ;
 fps . intra_error = ( double ) ( intra_error >> 8 ) + min_err ;
 fps . count = 1.0 ;
 fps . pcnt_inter = ( double ) intercount / cm -> MBs ;
 fps . pcnt_second_ref = ( double ) second_ref_count / cm -> MBs ;
 fps . pcnt_neutral = ( double ) neutral_count / cm -> MBs ;
 if ( mvcount > 0 ) {
 fps . MVr = ( double ) sum_mvr / mvcount ;
 fps . mvr_abs = ( double ) sum_mvr_abs / mvcount ;
 fps . MVc = ( double ) sum_mvc / mvcount ;
 fps . mvc_abs = ( double ) sum_mvc_abs / mvcount ;
 fps . MVrv = ( ( double ) sum_mvrs - ( fps . MVr * fps . MVr / mvcount ) ) / mvcount ;
 fps . MVcv = ( ( double ) sum_mvcs - ( fps . MVc * fps . MVc / mvcount ) ) / mvcount ;
 fps . mv_in_out_count = ( double ) sum_in_vectors / ( mvcount * 2 ) ;
 fps . new_mv_count = new_mv_count ;
 fps . pcnt_motion = ( double ) mvcount / cm -> MBs ;
 }
 else {
 fps . MVr = 0.0 ;
 fps . mvr_abs = 0.0 ;
 fps . MVc = 0.0 ;
 fps . mvc_abs = 0.0 ;
 fps . MVrv = 0.0 ;
 fps . MVcv = 0.0 ;
 fps . mv_in_out_count = 0.0 ;
 fps . new_mv_count = 0.0 ;
 fps . pcnt_motion = 0.0 ;
 }
 fps . duration = ( double ) ( source -> ts_end - source -> ts_start ) ;
 twopass -> this_frame_stats = fps ;
 output_stats ( & twopass -> this_frame_stats , cpi -> output_pkt_list ) ;
 accumulate_stats ( & twopass -> total_stats , & fps ) ;

 output_fpmb_stats ( twopass -> frame_mb_stats_buf , cm , cpi -> output_pkt_list ) ;
 }

 if ( ( twopass -> sr_update_lag > 3 ) || ( ( cm -> current_video_frame > 0 ) && ( twopass -> this_frame_stats . pcnt_inter > 0.20 ) && ( ( twopass -> this_frame_stats . intra_error / DOUBLE_DIVIDE_CHECK ( twopass -> this_frame_stats . coded_error ) ) > 2.0 ) ) ) {
 if ( gld_yv12 != NULL ) {
 vp8_yv12_copy_frame ( lst_yv12 , gld_yv12 ) ;
 }
 twopass -> sr_update_lag = 1 ;
 }
 else {
 ++ twopass -> sr_update_lag ;
 }
 vp9_extend_frame_borders ( new_yv12 ) ;
 if ( lc != NULL ) {
 vp9_update_reference_frames ( cpi ) ;
 }
 else {
 swap_yv12 ( lst_yv12 , new_yv12 ) ;
 }
 if ( cm -> current_video_frame == 0 && gld_yv12 != NULL && lc == NULL ) {
 vp8_yv12_copy_frame ( lst_yv12 , gld_yv12 ) ;
 }
 if ( 0 ) {
 char filename [ 512 ] ;
 FILE * recon_file ;
 snprintf ( filename , sizeof ( filename ) , "enc%04d.yuv" , ( int ) cm -> current_video_frame ) ;
 if ( cm -> current_video_frame == 0 ) recon_file = fopen ( filename , "wb" ) ;
 else recon_file = fopen ( filename , "ab" ) ;
 ( void ) fwrite ( lst_yv12 -> buffer_alloc , lst_yv12 -> frame_size , 1 , recon_file ) ;
 fclose ( recon_file ) ;
 }
 ++ cm -> current_video_frame ;
 if ( cpi -> use_svc ) vp9_inc_frame_in_layer ( cpi ) ;
 }
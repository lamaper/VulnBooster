void vp9_pick_inter_mode ( VP9_COMP * cpi , MACROBLOCK * x , const TileInfo * const tile , int mi_row , int mi_col , int * returnrate , int64_t * returndistortion , BLOCK_SIZE bsize , PICK_MODE_CONTEXT * ctx ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 MB_MODE_INFO * const mbmi = & xd -> mi [ 0 ] . src_mi -> mbmi ;
 struct macroblockd_plane * const pd = & xd -> plane [ 0 ] ;
 PREDICTION_MODE best_mode = ZEROMV ;
 MV_REFERENCE_FRAME ref_frame , best_ref_frame = LAST_FRAME ;
 TX_SIZE best_tx_size = MIN ( max_txsize_lookup [ bsize ] , tx_mode_to_biggest_tx_size [ cm -> tx_mode ] ) ;
 INTERP_FILTER best_pred_filter = EIGHTTAP ;
 int_mv frame_mv [ MB_MODE_COUNT ] [ MAX_REF_FRAMES ] ;
 struct buf_2d yv12_mb [ 4 ] [ MAX_MB_PLANE ] ;
 static const int flag_list [ 4 ] = {
 0 , VP9_LAST_FLAG , VP9_GOLD_FLAG , VP9_ALT_FLAG }
 ;
 int64_t best_rd = INT64_MAX ;
 int64_t this_rd = INT64_MAX ;
 uint8_t skip_txfm = 0 ;
 int rate = INT_MAX ;
 int64_t dist = INT64_MAX ;
 unsigned int var_y = UINT_MAX ;
 unsigned int sse_y = UINT_MAX ;
 const int intra_cost_penalty = * vp9_dc_quant ( cm -> base_qindex , cm -> y_dc_delta_q , cm -> bit_depth ) ;
 const int64_t inter_mode_thresh = RDCOST ( x -> rdmult , x -> rddiv , intra_cost_penalty , 0 ) ;
 const int intra_mode_cost = 50 ;
 const int8_t segment_id = mbmi -> segment_id ;
 const int * const rd_threshes = cpi -> rd . threshes [ segment_id ] [ bsize ] ;
 const int * const rd_thresh_freq_fact = cpi -> rd . thresh_freq_fact [ bsize ] ;
 INTERP_FILTER filter_ref = cm -> interp_filter ;
 const int bsl = mi_width_log2 ( bsize ) ;
 const int pred_filter_search = cm -> interp_filter == SWITCHABLE ? ( ( ( mi_row + mi_col ) >> bsl ) + get_chessboard_index ( cm -> current_video_frame ) ) & 0x1 : 0 ;
 int const_motion [ MAX_REF_FRAMES ] = {
 0 }
 ;
 const int bh = num_4x4_blocks_high_lookup [ bsize ] << 2 ;
 const int bw = num_4x4_blocks_wide_lookup [ bsize ] << 2 ;
 PRED_BUFFER tmp [ 4 ] ;
 DECLARE_ALIGNED_ARRAY ( 16 , uint8_t , pred_buf , 3 * 64 * 64 ) ;
 struct buf_2d orig_dst = pd -> dst ;
 PRED_BUFFER * best_pred = NULL ;
 PRED_BUFFER * this_mode_pred = NULL ;
 if ( cpi -> sf . reuse_inter_pred_sby ) {
 int i ;
 for ( i = 0 ;
 i < 3 ;
 i ++ ) {
 tmp [ i ] . data = & pred_buf [ bw * bh * i ] ;
 tmp [ i ] . stride = bw ;
 tmp [ i ] . in_use = 0 ;
 }
 tmp [ 3 ] . data = pd -> dst . buf ;
 tmp [ 3 ] . stride = pd -> dst . stride ;
 tmp [ 3 ] . in_use = 0 ;
 }
 x -> skip_encode = cpi -> sf . skip_encode_frame && x -> q_index < QIDX_SKIP_THRESH ;
 x -> skip = 0 ;
 * returnrate = INT_MAX ;
 * returndistortion = INT64_MAX ;
 vpx_memset ( mbmi , 0 , sizeof ( MB_MODE_INFO ) ) ;
 mbmi -> sb_type = bsize ;
 mbmi -> ref_frame [ 0 ] = NONE ;
 mbmi -> ref_frame [ 1 ] = NONE ;
 mbmi -> tx_size = MIN ( max_txsize_lookup [ bsize ] , tx_mode_to_biggest_tx_size [ cm -> tx_mode ] ) ;
 mbmi -> interp_filter = cm -> interp_filter == SWITCHABLE ? EIGHTTAP : cm -> interp_filter ;
 mbmi -> segment_id = segment_id ;
 for ( ref_frame = LAST_FRAME ;
 ref_frame <= ALTREF_FRAME ;
 ++ ref_frame ) {
 PREDICTION_MODE this_mode ;
 x -> pred_mv_sad [ ref_frame ] = INT_MAX ;
 frame_mv [ NEWMV ] [ ref_frame ] . as_int = INVALID_MV ;
 frame_mv [ ZEROMV ] [ ref_frame ] . as_int = 0 ;
 if ( xd -> up_available ) filter_ref = xd -> mi [ - xd -> mi_stride ] . src_mi -> mbmi . interp_filter ;
 else if ( xd -> left_available ) filter_ref = xd -> mi [ - 1 ] . src_mi -> mbmi . interp_filter ;
 if ( cpi -> ref_frame_flags & flag_list [ ref_frame ] ) {
 const YV12_BUFFER_CONFIG * yv12 = get_ref_frame_buffer ( cpi , ref_frame ) ;
 int_mv * const candidates = mbmi -> ref_mvs [ ref_frame ] ;
 const struct scale_factors * const sf = & cm -> frame_refs [ ref_frame - 1 ] . sf ;
 vp9_setup_pred_block ( xd , yv12_mb [ ref_frame ] , yv12 , mi_row , mi_col , sf , sf ) ;
 if ( ! cm -> error_resilient_mode ) vp9_find_mv_refs ( cm , xd , tile , xd -> mi [ 0 ] . src_mi , ref_frame , candidates , mi_row , mi_col ) ;
 else const_motion [ ref_frame ] = mv_refs_rt ( cm , xd , tile , xd -> mi [ 0 ] . src_mi , ref_frame , candidates , mi_row , mi_col ) ;
 vp9_find_best_ref_mvs ( xd , cm -> allow_high_precision_mv , candidates , & frame_mv [ NEARESTMV ] [ ref_frame ] , & frame_mv [ NEARMV ] [ ref_frame ] ) ;
 if ( ! vp9_is_scaled ( sf ) && bsize >= BLOCK_8X8 ) vp9_mv_pred ( cpi , x , yv12_mb [ ref_frame ] [ 0 ] . buf , yv12 -> y_stride , ref_frame , bsize ) ;
 }
 else {
 continue ;
 }
 xd -> plane [ 0 ] . pre [ 0 ] = yv12_mb [ ref_frame ] [ 0 ] ;
 clamp_mv2 ( & frame_mv [ NEARESTMV ] [ ref_frame ] . as_mv , xd ) ;
 clamp_mv2 ( & frame_mv [ NEARMV ] [ ref_frame ] . as_mv , xd ) ;
 mbmi -> ref_frame [ 0 ] = ref_frame ;
 for ( this_mode = NEARESTMV ;
 this_mode <= NEWMV ;
 ++ this_mode ) {
 int rate_mv = 0 ;
 int mode_rd_thresh ;
 if ( const_motion [ ref_frame ] && ( this_mode == NEARMV || this_mode == ZEROMV ) ) continue ;
 if ( ! ( cpi -> sf . inter_mode_mask [ bsize ] & ( 1 << this_mode ) ) ) continue ;
 mode_rd_thresh = rd_threshes [ mode_idx [ ref_frame - LAST_FRAME ] [ INTER_OFFSET ( this_mode ) ] ] ;
 if ( rd_less_than_thresh ( best_rd , mode_rd_thresh , rd_thresh_freq_fact [ this_mode ] ) ) continue ;
 if ( this_mode == NEWMV ) {
 if ( this_rd < ( int64_t ) ( 1 << num_pels_log2_lookup [ bsize ] ) ) continue ;
 if ( ! combined_motion_search ( cpi , x , bsize , mi_row , mi_col , & frame_mv [ NEWMV ] [ ref_frame ] , & rate_mv , best_rd ) ) continue ;
 }
 if ( this_mode != NEARESTMV && frame_mv [ this_mode ] [ ref_frame ] . as_int == frame_mv [ NEARESTMV ] [ ref_frame ] . as_int ) continue ;
 mbmi -> mode = this_mode ;
 mbmi -> mv [ 0 ] . as_int = frame_mv [ this_mode ] [ ref_frame ] . as_int ;
 if ( cpi -> sf . reuse_inter_pred_sby ) {
 if ( this_mode == NEARESTMV ) {
 this_mode_pred = & tmp [ 3 ] ;
 }
 else {
 this_mode_pred = & tmp [ get_pred_buffer ( tmp , 3 ) ] ;
 pd -> dst . buf = this_mode_pred -> data ;
 pd -> dst . stride = bw ;
 }
 }
 if ( ( this_mode == NEWMV || filter_ref == SWITCHABLE ) && pred_filter_search && ( ( mbmi -> mv [ 0 ] . as_mv . row & 0x07 ) != 0 || ( mbmi -> mv [ 0 ] . as_mv . col & 0x07 ) != 0 ) ) {
 int pf_rate [ 3 ] ;
 int64_t pf_dist [ 3 ] ;
 unsigned int pf_var [ 3 ] ;
 unsigned int pf_sse [ 3 ] ;
 TX_SIZE pf_tx_size [ 3 ] ;
 int64_t best_cost = INT64_MAX ;
 INTERP_FILTER best_filter = SWITCHABLE , filter ;
 PRED_BUFFER * current_pred = this_mode_pred ;
 for ( filter = EIGHTTAP ;
 filter <= EIGHTTAP_SHARP ;
 ++ filter ) {
 int64_t cost ;
 mbmi -> interp_filter = filter ;
 vp9_build_inter_predictors_sby ( xd , mi_row , mi_col , bsize ) ;
 model_rd_for_sb_y ( cpi , bsize , x , xd , & pf_rate [ filter ] , & pf_dist [ filter ] , & pf_var [ filter ] , & pf_sse [ filter ] ) ;
 cost = RDCOST ( x -> rdmult , x -> rddiv , vp9_get_switchable_rate ( cpi ) + pf_rate [ filter ] , pf_dist [ filter ] ) ;
 pf_tx_size [ filter ] = mbmi -> tx_size ;
 if ( cost < best_cost ) {
 best_filter = filter ;
 best_cost = cost ;
 skip_txfm = x -> skip_txfm [ 0 ] ;
 if ( cpi -> sf . reuse_inter_pred_sby ) {
 if ( this_mode_pred != current_pred ) {
 free_pred_buffer ( this_mode_pred ) ;
 this_mode_pred = current_pred ;
 }
 if ( filter < EIGHTTAP_SHARP ) {
 current_pred = & tmp [ get_pred_buffer ( tmp , 3 ) ] ;
 pd -> dst . buf = current_pred -> data ;
 pd -> dst . stride = bw ;
 }
 }
 }
 }
 if ( cpi -> sf . reuse_inter_pred_sby && this_mode_pred != current_pred ) free_pred_buffer ( current_pred ) ;
 mbmi -> interp_filter = best_filter ;
 mbmi -> tx_size = pf_tx_size [ mbmi -> interp_filter ] ;
 rate = pf_rate [ mbmi -> interp_filter ] ;
 dist = pf_dist [ mbmi -> interp_filter ] ;
 var_y = pf_var [ mbmi -> interp_filter ] ;
 sse_y = pf_sse [ mbmi -> interp_filter ] ;
 x -> skip_txfm [ 0 ] = skip_txfm ;
 }
 else {
 mbmi -> interp_filter = ( filter_ref == SWITCHABLE ) ? EIGHTTAP : filter_ref ;
 vp9_build_inter_predictors_sby ( xd , mi_row , mi_col , bsize ) ;
 model_rd_for_sb_y ( cpi , bsize , x , xd , & rate , & dist , & var_y , & sse_y ) ;
 }
 rate += rate_mv ;
 rate += cpi -> inter_mode_cost [ mbmi -> mode_context [ ref_frame ] ] [ INTER_OFFSET ( this_mode ) ] ;
 this_rd = RDCOST ( x -> rdmult , x -> rddiv , rate , dist ) ;
 if ( cpi -> allow_encode_breakout ) {
 encode_breakout_test ( cpi , x , bsize , mi_row , mi_col , ref_frame , this_mode , var_y , sse_y , yv12_mb , & rate , & dist ) ;
 if ( x -> skip ) {
 rate += rate_mv ;
 this_rd = RDCOST ( x -> rdmult , x -> rddiv , rate , dist ) ;
 }
 }

 vp9_denoiser_update_frame_stats ( mbmi , sse_y , this_mode , ctx ) ;
 }


 best_rd = this_rd ;
 * returnrate = rate ;
 * returndistortion = dist ;
 best_mode = this_mode ;
 best_pred_filter = mbmi -> interp_filter ;
 best_tx_size = mbmi -> tx_size ;
 best_ref_frame = ref_frame ;
 skip_txfm = x -> skip_txfm [ 0 ] ;
 if ( cpi -> sf . reuse_inter_pred_sby ) {
 free_pred_buffer ( best_pred ) ;
 best_pred = this_mode_pred ;
 }
 }
 else {
 if ( cpi -> sf . reuse_inter_pred_sby ) free_pred_buffer ( this_mode_pred ) ;
 }
 if ( x -> skip ) break ;
 }
 if ( best_rd < INT64_MAX ) break ;
 }
 if ( best_pred != NULL && cpi -> sf . reuse_inter_pred_sby && best_pred -> data != orig_dst . buf ) {
 pd -> dst = orig_dst ;
 vp9_convolve_copy ( best_pred -> data , bw , pd -> dst . buf , pd -> dst . stride , NULL , 0 , NULL , 0 , bw , bh ) ;
 }
 mbmi -> mode = best_mode ;
 mbmi -> interp_filter = best_pred_filter ;
 mbmi -> tx_size = best_tx_size ;
 mbmi -> ref_frame [ 0 ] = best_ref_frame ;
 mbmi -> mv [ 0 ] . as_int = frame_mv [ best_mode ] [ best_ref_frame ] . as_int ;
 xd -> mi [ 0 ] . src_mi -> bmi [ 0 ] . as_mv [ 0 ] . as_int = mbmi -> mv [ 0 ] . as_int ;
 x -> skip_txfm [ 0 ] = skip_txfm ;
 if ( ! x -> skip && best_rd > inter_mode_thresh && bsize <= cpi -> sf . max_intra_bsize ) {
 PREDICTION_MODE this_mode ;
 struct estimate_block_intra_args args = {
 cpi , x , DC_PRED , 0 , 0 }
 ;
 const TX_SIZE intra_tx_size = MIN ( max_txsize_lookup [ bsize ] , tx_mode_to_biggest_tx_size [ cpi -> common . tx_mode ] ) ;
 if ( cpi -> sf . reuse_inter_pred_sby ) {
 pd -> dst . buf = tmp [ 0 ] . data ;
 pd -> dst . stride = bw ;
 }
 for ( this_mode = DC_PRED ;
 this_mode <= DC_PRED ;
 ++ this_mode ) {
 const TX_SIZE saved_tx_size = mbmi -> tx_size ;
 args . mode = this_mode ;
 args . rate = 0 ;
 args . dist = 0 ;
 mbmi -> tx_size = intra_tx_size ;
 vp9_foreach_transformed_block_in_plane ( xd , bsize , 0 , estimate_block_intra , & args ) ;
 mbmi -> tx_size = saved_tx_size ;
 rate = args . rate ;
 dist = args . dist ;
 rate += cpi -> mbmode_cost [ this_mode ] ;
 rate += intra_cost_penalty ;
 this_rd = RDCOST ( x -> rdmult , x -> rddiv , rate , dist ) ;
 if ( this_rd + intra_mode_cost < best_rd ) {
 best_rd = this_rd ;
 * returnrate = rate ;
 * returndistortion = dist ;
 mbmi -> mode = this_mode ;
 mbmi -> tx_size = intra_tx_size ;
 mbmi -> ref_frame [ 0 ] = INTRA_FRAME ;
 mbmi -> uv_mode = this_mode ;
 mbmi -> mv [ 0 ] . as_int = INVALID_MV ;
 }
 else {
 x -> skip_txfm [ 0 ] = skip_txfm ;
 }
 }
 if ( cpi -> sf . reuse_inter_pred_sby ) pd -> dst = orig_dst ;
 }
 }
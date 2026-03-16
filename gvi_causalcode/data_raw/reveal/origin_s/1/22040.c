int64_t vp9_rd_pick_inter_mode_sb ( VP9_COMP * cpi , MACROBLOCK * x , const TileInfo * const tile , int mi_row , int mi_col , int * returnrate , int64_t * returndistortion , BLOCK_SIZE bsize , PICK_MODE_CONTEXT * ctx , int64_t best_rd_so_far ) {
 VP9_COMMON * const cm = & cpi -> common ;
 RD_OPT * const rd_opt = & cpi -> rd ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 MB_MODE_INFO * const mbmi = & xd -> mi [ 0 ] -> mbmi ;
 const struct segmentation * const seg = & cm -> seg ;
 struct macroblockd_plane * const pd = xd -> plane ;
 PREDICTION_MODE this_mode ;
 MV_REFERENCE_FRAME ref_frame , second_ref_frame ;
 unsigned char segment_id = mbmi -> segment_id ;
 int comp_pred , i , k ;
 int_mv frame_mv [ MB_MODE_COUNT ] [ MAX_REF_FRAMES ] ;
 struct buf_2d yv12_mb [ 4 ] [ MAX_MB_PLANE ] ;
 int_mv single_newmv [ MAX_REF_FRAMES ] = {
 {
 0 }
 }
 ;
 INTERP_FILTER single_inter_filter [ MB_MODE_COUNT ] [ MAX_REF_FRAMES ] ;
 int single_skippable [ MB_MODE_COUNT ] [ MAX_REF_FRAMES ] ;
 static const int flag_list [ 4 ] = {
 0 , VP9_LAST_FLAG , VP9_GOLD_FLAG , VP9_ALT_FLAG }
 ;
 int64_t best_rd = best_rd_so_far ;
 int64_t best_tx_rd [ TX_MODES ] ;
 int64_t best_tx_diff [ TX_MODES ] ;
 int64_t best_pred_diff [ REFERENCE_MODES ] ;
 int64_t best_pred_rd [ REFERENCE_MODES ] ;
 int64_t best_filter_rd [ SWITCHABLE_FILTER_CONTEXTS ] ;
 int64_t best_filter_diff [ SWITCHABLE_FILTER_CONTEXTS ] ;
 MB_MODE_INFO best_mbmode ;
 int best_mode_skippable = 0 ;
 int mode_index , best_mode_index = - 1 ;
 unsigned int ref_costs_single [ MAX_REF_FRAMES ] , ref_costs_comp [ MAX_REF_FRAMES ] ;
 vp9_prob comp_mode_p ;
 int64_t best_intra_rd = INT64_MAX ;
 int64_t best_inter_rd = INT64_MAX ;
 PREDICTION_MODE best_intra_mode = DC_PRED ;
 MV_REFERENCE_FRAME best_inter_ref_frame = LAST_FRAME ;
 int rate_uv_intra [ TX_SIZES ] , rate_uv_tokenonly [ TX_SIZES ] ;
 int64_t dist_uv [ TX_SIZES ] ;
 int skip_uv [ TX_SIZES ] ;
 PREDICTION_MODE mode_uv [ TX_SIZES ] ;
 int intra_cost_penalty = 20 * vp9_dc_quant ( cm -> base_qindex , cm -> y_dc_delta_q ) ;
 int best_skip2 = 0 ;
 int mode_skip_mask = 0 ;
 int mode_skip_start = cpi -> sf . mode_skip_start + 1 ;
 const int * const rd_threshes = rd_opt -> threshes [ segment_id ] [ bsize ] ;
 const int * const rd_thresh_freq_fact = rd_opt -> thresh_freq_fact [ bsize ] ;
 const int mode_search_skip_flags = cpi -> sf . mode_search_skip_flags ;
 const int intra_y_mode_mask = cpi -> sf . intra_y_mode_mask [ max_txsize_lookup [ bsize ] ] ;
 int inter_mode_mask = cpi -> sf . inter_mode_mask [ bsize ] ;
 vp9_zero ( best_mbmode ) ;
 x -> skip_encode = cpi -> sf . skip_encode_frame && x -> q_index < QIDX_SKIP_THRESH ;
 estimate_ref_frame_costs ( cm , xd , segment_id , ref_costs_single , ref_costs_comp , & comp_mode_p ) ;
 for ( i = 0 ;
 i < REFERENCE_MODES ;
 ++ i ) best_pred_rd [ i ] = INT64_MAX ;
 for ( i = 0 ;
 i < TX_MODES ;
 i ++ ) best_tx_rd [ i ] = INT64_MAX ;
 for ( i = 0 ;
 i < SWITCHABLE_FILTER_CONTEXTS ;
 i ++ ) best_filter_rd [ i ] = INT64_MAX ;
 for ( i = 0 ;
 i < TX_SIZES ;
 i ++ ) rate_uv_intra [ i ] = INT_MAX ;
 for ( i = 0 ;
 i < MAX_REF_FRAMES ;
 ++ i ) x -> pred_sse [ i ] = INT_MAX ;
 for ( i = 0 ;
 i < MB_MODE_COUNT ;
 ++ i ) {
 for ( k = 0 ;
 k < MAX_REF_FRAMES ;
 ++ k ) {
 single_inter_filter [ i ] [ k ] = SWITCHABLE ;
 single_skippable [ i ] [ k ] = 0 ;
 }
 }
 * returnrate = INT_MAX ;
 for ( ref_frame = LAST_FRAME ;
 ref_frame <= ALTREF_FRAME ;
 ++ ref_frame ) {
 x -> pred_mv_sad [ ref_frame ] = INT_MAX ;
 if ( cpi -> ref_frame_flags & flag_list [ ref_frame ] ) {
 setup_buffer_inter ( cpi , x , tile , ref_frame , bsize , mi_row , mi_col , frame_mv [ NEARESTMV ] , frame_mv [ NEARMV ] , yv12_mb ) ;
 }
 frame_mv [ NEWMV ] [ ref_frame ] . as_int = INVALID_MV ;
 frame_mv [ ZEROMV ] [ ref_frame ] . as_int = 0 ;
 }
 for ( ref_frame = LAST_FRAME ;
 ref_frame <= ALTREF_FRAME ;
 ++ ref_frame ) {
 static const int ref_frame_mask_all [ ] = {
 0x0 , 0x123291 , 0x25c444 , 0x39b722 }
 ;
 static const int ref_frame_mask_fixedmv [ ] = {
 0x0 , 0x121281 , 0x24c404 , 0x080102 }
 ;
 if ( ! ( cpi -> ref_frame_flags & flag_list [ ref_frame ] ) ) {
 mode_skip_mask |= ref_frame_mask_all [ ref_frame ] ;
 }
 else if ( cpi -> sf . reference_masking ) {
 for ( i = LAST_FRAME ;
 i <= ALTREF_FRAME ;
 ++ i ) {
 if ( ( x -> pred_mv_sad [ ref_frame ] >> 2 ) > x -> pred_mv_sad [ i ] ) {
 mode_skip_mask |= ref_frame_mask_fixedmv [ ref_frame ] ;
 break ;
 }
 }
 }
 if ( vp9_segfeature_active ( seg , segment_id , SEG_LVL_REF_FRAME ) && vp9_get_segdata ( seg , segment_id , SEG_LVL_REF_FRAME ) != ( int ) ref_frame ) {
 mode_skip_mask |= ref_frame_mask_all [ ref_frame ] ;
 }
 }
 if ( ! vp9_segfeature_active ( seg , segment_id , SEG_LVL_REF_FRAME ) ) {
 if ( cpi -> rc . is_src_frame_alt_ref && ( cpi -> oxcf . arnr_max_frames == 0 ) ) {
 mode_skip_mask = ~ ( ( 1 << THR_NEARESTA ) | ( 1 << THR_NEARA ) | ( 1 << THR_ZEROA ) ) ;
 if ( frame_mv [ NEARMV ] [ ALTREF_FRAME ] . as_int != 0 ) mode_skip_mask |= ( 1 << THR_NEARA ) ;
 if ( frame_mv [ NEARESTMV ] [ ALTREF_FRAME ] . as_int != 0 ) mode_skip_mask |= ( 1 << THR_NEARESTA ) ;
 }
 }
 if ( bsize > cpi -> sf . max_intra_bsize ) {
 const int all_intra_modes = ( 1 << THR_DC ) | ( 1 << THR_TM ) | ( 1 << THR_H_PRED ) | ( 1 << THR_V_PRED ) | ( 1 << THR_D135_PRED ) | ( 1 << THR_D207_PRED ) | ( 1 << THR_D153_PRED ) | ( 1 << THR_D63_PRED ) | ( 1 << THR_D117_PRED ) | ( 1 << THR_D45_PRED ) ;
 mode_skip_mask |= all_intra_modes ;
 }
 for ( mode_index = 0 ;
 mode_index < MAX_MODES ;
 ++ mode_index ) {
 int mode_excluded = 0 ;
 int64_t this_rd = INT64_MAX ;
 int disable_skip = 0 ;
 int compmode_cost = 0 ;
 int rate2 = 0 , rate_y = 0 , rate_uv = 0 ;
 int64_t distortion2 = 0 , distortion_y = 0 , distortion_uv = 0 ;
 int skippable = 0 ;
 int64_t tx_cache [ TX_MODES ] ;
 int i ;
 int this_skip2 = 0 ;
 int64_t total_sse = INT64_MAX ;
 int early_term = 0 ;
 this_mode = vp9_mode_order [ mode_index ] . mode ;
 ref_frame = vp9_mode_order [ mode_index ] . ref_frame [ 0 ] ;
 if ( ref_frame != INTRA_FRAME && ! ( inter_mode_mask & ( 1 << this_mode ) ) ) continue ;
 second_ref_frame = vp9_mode_order [ mode_index ] . ref_frame [ 1 ] ;
 if ( mode_index == mode_skip_start && best_mode_index >= 0 ) {
 switch ( vp9_mode_order [ best_mode_index ] . ref_frame [ 0 ] ) {
 case INTRA_FRAME : break ;
 case LAST_FRAME : mode_skip_mask |= LAST_FRAME_MODE_MASK ;
 break ;
 case GOLDEN_FRAME : mode_skip_mask |= GOLDEN_FRAME_MODE_MASK ;
 break ;
 case ALTREF_FRAME : mode_skip_mask |= ALT_REF_MODE_MASK ;
 break ;
 case NONE : case MAX_REF_FRAMES : assert ( 0 && "Invalid Reference frame" ) ;
 break ;
 }
 }
 if ( cpi -> sf . alt_ref_search_fp && cpi -> rc . is_src_frame_alt_ref ) {
 mode_skip_mask = 0 ;
 if ( ! ( ref_frame == ALTREF_FRAME && second_ref_frame == NONE ) ) continue ;
 }
 if ( mode_skip_mask & ( 1 << mode_index ) ) continue ;
 if ( rd_less_than_thresh ( best_rd , rd_threshes [ mode_index ] , rd_thresh_freq_fact [ mode_index ] ) ) continue ;
 if ( cpi -> sf . motion_field_mode_search ) {
 const int mi_width = MIN ( num_8x8_blocks_wide_lookup [ bsize ] , tile -> mi_col_end - mi_col ) ;
 const int mi_height = MIN ( num_8x8_blocks_high_lookup [ bsize ] , tile -> mi_row_end - mi_row ) ;
 const int bsl = mi_width_log2 ( bsize ) ;
 int cb_partition_search_ctrl = ( ( ( mi_row + mi_col ) >> bsl ) + get_chessboard_index ( cm -> current_video_frame ) ) & 0x1 ;
 MB_MODE_INFO * ref_mbmi ;
 int const_motion = 1 ;
 int skip_ref_frame = ! cb_partition_search_ctrl ;
 MV_REFERENCE_FRAME rf = NONE ;
 int_mv ref_mv ;
 ref_mv . as_int = INVALID_MV ;
 if ( ( mi_row - 1 ) >= tile -> mi_row_start ) {
 ref_mv = xd -> mi [ - xd -> mi_stride ] -> mbmi . mv [ 0 ] ;
 rf = xd -> mi [ - xd -> mi_stride ] -> mbmi . ref_frame [ 0 ] ;
 for ( i = 0 ;
 i < mi_width ;
 ++ i ) {
 ref_mbmi = & xd -> mi [ - xd -> mi_stride + i ] -> mbmi ;
 const_motion &= ( ref_mv . as_int == ref_mbmi -> mv [ 0 ] . as_int ) && ( ref_frame == ref_mbmi -> ref_frame [ 0 ] ) ;
 skip_ref_frame &= ( rf == ref_mbmi -> ref_frame [ 0 ] ) ;
 }
 }
 if ( ( mi_col - 1 ) >= tile -> mi_col_start ) {
 if ( ref_mv . as_int == INVALID_MV ) ref_mv = xd -> mi [ - 1 ] -> mbmi . mv [ 0 ] ;
 if ( rf == NONE ) rf = xd -> mi [ - 1 ] -> mbmi . ref_frame [ 0 ] ;
 for ( i = 0 ;
 i < mi_height ;
 ++ i ) {
 ref_mbmi = & xd -> mi [ i * xd -> mi_stride - 1 ] -> mbmi ;
 const_motion &= ( ref_mv . as_int == ref_mbmi -> mv [ 0 ] . as_int ) && ( ref_frame == ref_mbmi -> ref_frame [ 0 ] ) ;
 skip_ref_frame &= ( rf == ref_mbmi -> ref_frame [ 0 ] ) ;
 }
 }
 if ( skip_ref_frame && this_mode != NEARESTMV && this_mode != NEWMV ) if ( rf > INTRA_FRAME ) if ( ref_frame != rf ) continue ;
 if ( const_motion ) if ( this_mode == NEARMV || this_mode == ZEROMV ) continue ;
 }
 comp_pred = second_ref_frame > INTRA_FRAME ;
 if ( comp_pred ) {
 if ( ! cm -> allow_comp_inter_inter ) continue ;
 if ( ( mode_search_skip_flags & FLAG_SKIP_COMP_BESTINTRA ) && best_mode_index >= 0 && vp9_mode_order [ best_mode_index ] . ref_frame [ 0 ] == INTRA_FRAME ) continue ;
 if ( ( mode_search_skip_flags & FLAG_SKIP_COMP_REFMISMATCH ) && ref_frame != best_inter_ref_frame && second_ref_frame != best_inter_ref_frame ) continue ;
 mode_excluded = cm -> reference_mode == SINGLE_REFERENCE ;
 }
 else {
 if ( ref_frame != INTRA_FRAME ) mode_excluded = cm -> reference_mode == COMPOUND_REFERENCE ;
 }
 if ( ref_frame == INTRA_FRAME ) {
 if ( cpi -> sf . adaptive_mode_search ) if ( ( x -> source_variance << num_pels_log2_lookup [ bsize ] ) > best_intra_rd ) continue ;
 if ( ! ( intra_y_mode_mask & ( 1 << this_mode ) ) ) continue ;
 if ( this_mode != DC_PRED ) {
 const unsigned int skip_intra_var_thresh = 64 ;
 if ( ( mode_search_skip_flags & FLAG_SKIP_INTRA_LOWVAR ) && x -> source_variance < skip_intra_var_thresh ) continue ;
 if ( ( mode_search_skip_flags & FLAG_SKIP_INTRA_BESTINTER ) && ( this_mode >= D45_PRED && this_mode <= TM_PRED ) ) {
 if ( best_mode_index >= 0 && vp9_mode_order [ best_mode_index ] . ref_frame [ 0 ] > INTRA_FRAME ) continue ;
 }
 if ( mode_search_skip_flags & FLAG_SKIP_INTRA_DIRMISMATCH ) {
 if ( conditional_skipintra ( this_mode , best_intra_mode ) ) continue ;
 }
 }
 }
 else {
 const MV_REFERENCE_FRAME ref_frames [ 2 ] = {
 ref_frame , second_ref_frame }
 ;
 if ( ! check_best_zero_mv ( cpi , mbmi -> mode_context , frame_mv , inter_mode_mask , this_mode , ref_frames ) ) continue ;
 }
 mbmi -> mode = this_mode ;
 mbmi -> uv_mode = DC_PRED ;
 mbmi -> ref_frame [ 0 ] = ref_frame ;
 mbmi -> ref_frame [ 1 ] = second_ref_frame ;
 mbmi -> interp_filter = cm -> interp_filter == SWITCHABLE ? EIGHTTAP : cm -> interp_filter ;
 mbmi -> mv [ 0 ] . as_int = mbmi -> mv [ 1 ] . as_int = 0 ;
 x -> skip = 0 ;
 set_ref_ptrs ( cm , xd , ref_frame , second_ref_frame ) ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 i ++ ) {
 xd -> plane [ i ] . pre [ 0 ] = yv12_mb [ ref_frame ] [ i ] ;
 if ( comp_pred ) xd -> plane [ i ] . pre [ 1 ] = yv12_mb [ second_ref_frame ] [ i ] ;
 }
 for ( i = 0 ;
 i < TX_MODES ;
 ++ i ) tx_cache [ i ] = INT64_MAX ;
 if ( ref_frame == INTRA_FRAME ) {
 TX_SIZE uv_tx ;
 super_block_yrd ( cpi , x , & rate_y , & distortion_y , & skippable , NULL , bsize , tx_cache , best_rd ) ;
 if ( rate_y == INT_MAX ) continue ;
 uv_tx = get_uv_tx_size_impl ( mbmi -> tx_size , bsize , pd [ 1 ] . subsampling_x , pd [ 1 ] . subsampling_y ) ;
 if ( rate_uv_intra [ uv_tx ] == INT_MAX ) {
 choose_intra_uv_mode ( cpi , ctx , bsize , uv_tx , & rate_uv_intra [ uv_tx ] , & rate_uv_tokenonly [ uv_tx ] , & dist_uv [ uv_tx ] , & skip_uv [ uv_tx ] , & mode_uv [ uv_tx ] ) ;
 }
 rate_uv = rate_uv_tokenonly [ uv_tx ] ;
 distortion_uv = dist_uv [ uv_tx ] ;
 skippable = skippable && skip_uv [ uv_tx ] ;
 mbmi -> uv_mode = mode_uv [ uv_tx ] ;
 rate2 = rate_y + cpi -> mbmode_cost [ mbmi -> mode ] + rate_uv_intra [ uv_tx ] ;
 if ( this_mode != DC_PRED && this_mode != TM_PRED ) rate2 += intra_cost_penalty ;
 distortion2 = distortion_y + distortion_uv ;
 }
 else {
 this_rd = handle_inter_mode ( cpi , x , bsize , tx_cache , & rate2 , & distortion2 , & skippable , & rate_y , & distortion_y , & rate_uv , & distortion_uv , & disable_skip , frame_mv , mi_row , mi_col , single_newmv , single_inter_filter , single_skippable , & total_sse , best_rd ) ;
 if ( this_rd == INT64_MAX ) continue ;
 compmode_cost = vp9_cost_bit ( comp_mode_p , comp_pred ) ;
 if ( cm -> reference_mode == REFERENCE_MODE_SELECT ) rate2 += compmode_cost ;
 }
 if ( comp_pred ) {
 rate2 += ref_costs_comp [ ref_frame ] ;
 }
 else {
 rate2 += ref_costs_single [ ref_frame ] ;
 }
 if ( ! disable_skip ) {
 if ( skippable ) {
 vp9_prob skip_prob = vp9_get_skip_prob ( cm , xd ) ;
 rate2 -= ( rate_y + rate_uv ) ;
 rate_uv = 0 ;
 if ( skip_prob ) {
 int prob_skip_cost = vp9_cost_bit ( skip_prob , 1 ) ;
 rate2 += prob_skip_cost ;
 }
 }
 else if ( ref_frame != INTRA_FRAME && ! xd -> lossless ) {
 if ( RDCOST ( x -> rdmult , x -> rddiv , rate_y + rate_uv , distortion2 ) < RDCOST ( x -> rdmult , x -> rddiv , 0 , total_sse ) ) {
 rate2 += vp9_cost_bit ( vp9_get_skip_prob ( cm , xd ) , 0 ) ;
 }
 else {
 rate2 += vp9_cost_bit ( vp9_get_skip_prob ( cm , xd ) , 1 ) ;
 distortion2 = total_sse ;
 assert ( total_sse >= 0 ) ;
 rate2 -= ( rate_y + rate_uv ) ;
 rate_y = 0 ;
 rate_uv = 0 ;
 this_skip2 = 1 ;
 }
 }
 else {
 rate2 += vp9_cost_bit ( vp9_get_skip_prob ( cm , xd ) , 0 ) ;
 }
 this_rd = RDCOST ( x -> rdmult , x -> rddiv , rate2 , distortion2 ) ;
 }
 if ( ref_frame == INTRA_FRAME ) {
 if ( this_rd < best_intra_rd ) {
 best_intra_rd = this_rd ;
 best_intra_mode = mbmi -> mode ;
 }
 }
 else {
 if ( ! comp_pred && ! mode_excluded && this_rd < best_inter_rd ) {
 best_inter_rd = this_rd ;
 best_inter_ref_frame = ref_frame ;
 }
 }
 if ( ! disable_skip && ref_frame == INTRA_FRAME ) {
 for ( i = 0 ;
 i < REFERENCE_MODES ;
 ++ i ) best_pred_rd [ i ] = MIN ( best_pred_rd [ i ] , this_rd ) ;
 for ( i = 0 ;
 i < SWITCHABLE_FILTER_CONTEXTS ;
 i ++ ) best_filter_rd [ i ] = MIN ( best_filter_rd [ i ] , this_rd ) ;
 }
 if ( this_rd < best_rd || x -> skip ) {
 int max_plane = MAX_MB_PLANE ;
 if ( ! mode_excluded ) {
 best_mode_index = mode_index ;
 if ( ref_frame == INTRA_FRAME ) {
 mbmi -> mv [ 0 ] . as_int = 0 ;
 max_plane = 1 ;
 }
 else {
 best_intra_rd = x -> pred_sse [ ref_frame ] ;
 }
 * returnrate = rate2 ;
 * returndistortion = distortion2 ;
 best_rd = this_rd ;
 best_mbmode = * mbmi ;
 best_skip2 = this_skip2 ;
 best_mode_skippable = skippable ;
 if ( ! x -> select_tx_size ) swap_block_ptr ( x , ctx , 1 , 0 , 0 , max_plane ) ;
 vpx_memcpy ( ctx -> zcoeff_blk , x -> zcoeff_blk [ mbmi -> tx_size ] , sizeof ( uint8_t ) * ctx -> num_4x4_blk ) ;
 if ( ( mode_search_skip_flags & FLAG_EARLY_TERMINATE ) && ( mode_index > MIN_EARLY_TERM_INDEX ) ) {
 const int qstep = xd -> plane [ 0 ] . dequant [ 1 ] ;
 int scale = 4 ;
 if ( x -> source_variance < UINT_MAX ) {
 const int var_adjust = ( x -> source_variance < 16 ) ;
 scale -= var_adjust ;
 }
 if ( ref_frame > INTRA_FRAME && distortion2 * scale < qstep * qstep ) {
 early_term = 1 ;
 }
 }
 }
 }
 if ( ! disable_skip && ref_frame != INTRA_FRAME ) {
 int64_t single_rd , hybrid_rd , single_rate , hybrid_rate ;
 if ( cm -> reference_mode == REFERENCE_MODE_SELECT ) {
 single_rate = rate2 - compmode_cost ;
 hybrid_rate = rate2 ;
 }
 else {
 single_rate = rate2 ;
 hybrid_rate = rate2 + compmode_cost ;
 }
 single_rd = RDCOST ( x -> rdmult , x -> rddiv , single_rate , distortion2 ) ;
 hybrid_rd = RDCOST ( x -> rdmult , x -> rddiv , hybrid_rate , distortion2 ) ;
 if ( ! comp_pred ) {
 if ( single_rd < best_pred_rd [ SINGLE_REFERENCE ] ) {
 best_pred_rd [ SINGLE_REFERENCE ] = single_rd ;
 }
 }
 else {
 if ( single_rd < best_pred_rd [ COMPOUND_REFERENCE ] ) {
 best_pred_rd [ COMPOUND_REFERENCE ] = single_rd ;
 }
 }
 if ( hybrid_rd < best_pred_rd [ REFERENCE_MODE_SELECT ] ) best_pred_rd [ REFERENCE_MODE_SELECT ] = hybrid_rd ;
 if ( ! mode_excluded && cm -> interp_filter != BILINEAR ) {
 int64_t ref = rd_opt -> filter_cache [ cm -> interp_filter == SWITCHABLE ? SWITCHABLE_FILTERS : cm -> interp_filter ] ;
 for ( i = 0 ;
 i < SWITCHABLE_FILTER_CONTEXTS ;
 i ++ ) {
 int64_t adj_rd ;
 if ( ref == INT64_MAX ) adj_rd = 0 ;
 else if ( rd_opt -> filter_cache [ i ] == INT64_MAX ) adj_rd = rd_opt -> mask_filter - ref + 10 ;
 else adj_rd = rd_opt -> filter_cache [ i ] - ref ;
 adj_rd += this_rd ;
 best_filter_rd [ i ] = MIN ( best_filter_rd [ i ] , adj_rd ) ;
 }
 }
 }
 if ( bsize < BLOCK_32X32 ) {
 if ( bsize < BLOCK_16X16 ) tx_cache [ ALLOW_16X16 ] = tx_cache [ ALLOW_8X8 ] ;
 tx_cache [ ALLOW_32X32 ] = tx_cache [ ALLOW_16X16 ] ;
 }
 if ( ! mode_excluded && this_rd != INT64_MAX ) {
 for ( i = 0 ;
 i < TX_MODES && tx_cache [ i ] < INT64_MAX ;
 i ++ ) {
 int64_t adj_rd = INT64_MAX ;
 adj_rd = this_rd + tx_cache [ i ] - tx_cache [ cm -> tx_mode ] ;
 if ( adj_rd < best_tx_rd [ i ] ) best_tx_rd [ i ] = adj_rd ;
 }
 }
 if ( early_term ) break ;
 if ( x -> skip && ! comp_pred ) break ;
 }
 if ( best_mbmode . mode == NEWMV ) {
 const MV_REFERENCE_FRAME refs [ 2 ] = {
 best_mbmode . ref_frame [ 0 ] , best_mbmode . ref_frame [ 1 ] }
 ;
 int comp_pred_mode = refs [ 1 ] > INTRA_FRAME ;
 if ( frame_mv [ NEARESTMV ] [ refs [ 0 ] ] . as_int == best_mbmode . mv [ 0 ] . as_int && ( ( comp_pred_mode && frame_mv [ NEARESTMV ] [ refs [ 1 ] ] . as_int == best_mbmode . mv [ 1 ] . as_int ) || ! comp_pred_mode ) ) best_mbmode . mode = NEARESTMV ;
 else if ( frame_mv [ NEARMV ] [ refs [ 0 ] ] . as_int == best_mbmode . mv [ 0 ] . as_int && ( ( comp_pred_mode && frame_mv [ NEARMV ] [ refs [ 1 ] ] . as_int == best_mbmode . mv [ 1 ] . as_int ) || ! comp_pred_mode ) ) best_mbmode . mode = NEARMV ;
 else if ( best_mbmode . mv [ 0 ] . as_int == 0 && ( ( comp_pred_mode && best_mbmode . mv [ 1 ] . as_int == 0 ) || ! comp_pred_mode ) ) best_mbmode . mode = ZEROMV ;
 }
 if ( best_mode_index < 0 || best_rd >= best_rd_so_far ) return INT64_MAX ;
 if ( cpi -> sf . use_uv_intra_rd_estimate ) {
 if ( vp9_mode_order [ best_mode_index ] . ref_frame [ 0 ] == INTRA_FRAME ) {
 TX_SIZE uv_tx_size ;
 * mbmi = best_mbmode ;
 uv_tx_size = get_uv_tx_size ( mbmi , & xd -> plane [ 1 ] ) ;
 rd_pick_intra_sbuv_mode ( cpi , x , ctx , & rate_uv_intra [ uv_tx_size ] , & rate_uv_tokenonly [ uv_tx_size ] , & dist_uv [ uv_tx_size ] , & skip_uv [ uv_tx_size ] , bsize < BLOCK_8X8 ? BLOCK_8X8 : bsize , uv_tx_size ) ;
 }
 }
 assert ( ( cm -> interp_filter == SWITCHABLE ) || ( cm -> interp_filter == best_mbmode . interp_filter ) || ! is_inter_block ( & best_mbmode ) ) ;
 update_rd_thresh_fact ( cpi , bsize , best_mode_index ) ;
 * mbmi = best_mbmode ;
 x -> skip |= best_skip2 ;
 for ( i = 0 ;
 i < REFERENCE_MODES ;
 ++ i ) {
 if ( best_pred_rd [ i ] == INT64_MAX ) best_pred_diff [ i ] = INT_MIN ;
 else best_pred_diff [ i ] = best_rd - best_pred_rd [ i ] ;
 }
 if ( ! x -> skip ) {
 for ( i = 0 ;
 i < SWITCHABLE_FILTER_CONTEXTS ;
 i ++ ) {
 if ( best_filter_rd [ i ] == INT64_MAX ) best_filter_diff [ i ] = 0 ;
 else best_filter_diff [ i ] = best_rd - best_filter_rd [ i ] ;
 }
 if ( cm -> interp_filter == SWITCHABLE ) assert ( best_filter_diff [ SWITCHABLE_FILTERS ] == 0 ) ;
 for ( i = 0 ;
 i < TX_MODES ;
 i ++ ) {
 if ( best_tx_rd [ i ] == INT64_MAX ) best_tx_diff [ i ] = 0 ;
 else best_tx_diff [ i ] = best_rd - best_tx_rd [ i ] ;
 }
 }
 else {
 vp9_zero ( best_filter_diff ) ;
 vp9_zero ( best_tx_diff ) ;
 }
 set_ref_ptrs ( cm , xd , mbmi -> ref_frame [ 0 ] , mbmi -> ref_frame [ 1 ] ) ;
 store_coding_context ( x , ctx , best_mode_index , best_pred_diff , best_tx_diff , best_filter_diff , best_mode_skippable ) ;
 return best_rd ;
 }
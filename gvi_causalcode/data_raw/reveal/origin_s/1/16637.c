int64_t vp9_rd_pick_inter_mode_sub8x8 ( VP9_COMP * cpi , MACROBLOCK * x , const TileInfo * const tile , int mi_row , int mi_col , int * returnrate , int64_t * returndistortion , BLOCK_SIZE bsize , PICK_MODE_CONTEXT * ctx , int64_t best_rd_so_far ) {
 VP9_COMMON * const cm = & cpi -> common ;
 RD_OPT * const rd_opt = & cpi -> rd ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 MB_MODE_INFO * const mbmi = & xd -> mi [ 0 ] -> mbmi ;
 const struct segmentation * const seg = & cm -> seg ;
 MV_REFERENCE_FRAME ref_frame , second_ref_frame ;
 unsigned char segment_id = mbmi -> segment_id ;
 int comp_pred , i ;
 int_mv frame_mv [ MB_MODE_COUNT ] [ MAX_REF_FRAMES ] ;
 struct buf_2d yv12_mb [ 4 ] [ MAX_MB_PLANE ] ;
 static const int flag_list [ 4 ] = {
 0 , VP9_LAST_FLAG , VP9_GOLD_FLAG , VP9_ALT_FLAG }
 ;
 int64_t best_rd = best_rd_so_far ;
 int64_t best_yrd = best_rd_so_far ;
 static const int64_t best_tx_diff [ TX_MODES ] = {
 0 }
 ;
 int64_t best_pred_diff [ REFERENCE_MODES ] ;
 int64_t best_pred_rd [ REFERENCE_MODES ] ;
 int64_t best_filter_rd [ SWITCHABLE_FILTER_CONTEXTS ] ;
 int64_t best_filter_diff [ SWITCHABLE_FILTER_CONTEXTS ] ;
 MB_MODE_INFO best_mbmode ;
 int ref_index , best_ref_index = 0 ;
 unsigned int ref_costs_single [ MAX_REF_FRAMES ] , ref_costs_comp [ MAX_REF_FRAMES ] ;
 vp9_prob comp_mode_p ;
 int64_t best_inter_rd = INT64_MAX ;
 MV_REFERENCE_FRAME best_inter_ref_frame = LAST_FRAME ;
 INTERP_FILTER tmp_best_filter = SWITCHABLE ;
 int rate_uv_intra , rate_uv_tokenonly ;
 int64_t dist_uv ;
 int skip_uv ;
 PREDICTION_MODE mode_uv = DC_PRED ;
 int intra_cost_penalty = 20 * vp9_dc_quant ( cm -> base_qindex , cm -> y_dc_delta_q ) ;
 int_mv seg_mvs [ 4 ] [ MAX_REF_FRAMES ] ;
 b_mode_info best_bmodes [ 4 ] ;
 int best_skip2 = 0 ;
 int mode_skip_mask = 0 ;
 x -> skip_encode = cpi -> sf . skip_encode_frame && x -> q_index < QIDX_SKIP_THRESH ;
 vpx_memset ( x -> zcoeff_blk [ TX_4X4 ] , 0 , 4 ) ;
 vp9_zero ( best_mbmode ) ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 int j ;
 for ( j = 0 ;
 j < MAX_REF_FRAMES ;
 j ++ ) seg_mvs [ i ] [ j ] . as_int = INVALID_MV ;
 }
 estimate_ref_frame_costs ( cm , xd , segment_id , ref_costs_single , ref_costs_comp , & comp_mode_p ) ;
 for ( i = 0 ;
 i < REFERENCE_MODES ;
 ++ i ) best_pred_rd [ i ] = INT64_MAX ;
 for ( i = 0 ;
 i < SWITCHABLE_FILTER_CONTEXTS ;
 i ++ ) best_filter_rd [ i ] = INT64_MAX ;
 rate_uv_intra = INT_MAX ;
 * returnrate = INT_MAX ;
 for ( ref_frame = LAST_FRAME ;
 ref_frame <= ALTREF_FRAME ;
 ref_frame ++ ) {
 if ( cpi -> ref_frame_flags & flag_list [ ref_frame ] ) {
 setup_buffer_inter ( cpi , x , tile , ref_frame , bsize , mi_row , mi_col , frame_mv [ NEARESTMV ] , frame_mv [ NEARMV ] , yv12_mb ) ;
 }
 frame_mv [ NEWMV ] [ ref_frame ] . as_int = INVALID_MV ;
 frame_mv [ ZEROMV ] [ ref_frame ] . as_int = 0 ;
 }
 for ( ref_index = 0 ;
 ref_index < MAX_REFS ;
 ++ ref_index ) {
 int mode_excluded = 0 ;
 int64_t this_rd = INT64_MAX ;
 int disable_skip = 0 ;
 int compmode_cost = 0 ;
 int rate2 = 0 , rate_y = 0 , rate_uv = 0 ;
 int64_t distortion2 = 0 , distortion_y = 0 , distortion_uv = 0 ;
 int skippable = 0 ;
 int i ;
 int this_skip2 = 0 ;
 int64_t total_sse = INT_MAX ;
 int early_term = 0 ;
 ref_frame = vp9_ref_order [ ref_index ] . ref_frame [ 0 ] ;
 second_ref_frame = vp9_ref_order [ ref_index ] . ref_frame [ 1 ] ;
 if ( ref_index > 2 && cpi -> sf . mode_skip_start < MAX_MODES ) {
 if ( ref_index == 3 ) {
 switch ( vp9_ref_order [ best_ref_index ] . ref_frame [ 0 ] ) {
 case INTRA_FRAME : mode_skip_mask = 0 ;
 break ;
 case LAST_FRAME : mode_skip_mask = 0x0010 ;
 break ;
 case GOLDEN_FRAME : mode_skip_mask = 0x0008 ;
 break ;
 case ALTREF_FRAME : mode_skip_mask = 0x0000 ;
 break ;
 case NONE : case MAX_REF_FRAMES : assert ( 0 && "Invalid Reference frame" ) ;
 break ;
 }
 }
 if ( mode_skip_mask & ( 1 << ref_index ) ) continue ;
 }
 if ( rd_less_than_thresh ( best_rd , rd_opt -> threshes [ segment_id ] [ bsize ] [ ref_index ] , rd_opt -> thresh_freq_fact [ bsize ] [ ref_index ] ) ) continue ;
 if ( ref_frame > INTRA_FRAME && ! ( cpi -> ref_frame_flags & flag_list [ ref_frame ] ) ) {
 continue ;
 }
 comp_pred = second_ref_frame > INTRA_FRAME ;
 if ( comp_pred ) {
 if ( ! cm -> allow_comp_inter_inter ) continue ;
 if ( ! ( cpi -> ref_frame_flags & flag_list [ second_ref_frame ] ) ) continue ;
 if ( vp9_segfeature_active ( seg , segment_id , SEG_LVL_REF_FRAME ) ) continue ;
 if ( ( cpi -> sf . mode_search_skip_flags & FLAG_SKIP_COMP_BESTINTRA ) && vp9_ref_order [ best_ref_index ] . ref_frame [ 0 ] == INTRA_FRAME ) continue ;
 if ( ( cpi -> sf . mode_search_skip_flags & FLAG_SKIP_COMP_REFMISMATCH ) && ref_frame != best_inter_ref_frame && second_ref_frame != best_inter_ref_frame ) continue ;
 }
 if ( ref_frame > INTRA_FRAME && vp9_is_scaled ( & cm -> frame_refs [ ref_frame - 1 ] . sf ) ) continue ;
 if ( second_ref_frame > INTRA_FRAME && vp9_is_scaled ( & cm -> frame_refs [ second_ref_frame - 1 ] . sf ) ) continue ;
 if ( comp_pred ) mode_excluded = cm -> reference_mode == SINGLE_REFERENCE ;
 else if ( ref_frame != INTRA_FRAME ) mode_excluded = cm -> reference_mode == COMPOUND_REFERENCE ;
 if ( vp9_segfeature_active ( seg , segment_id , SEG_LVL_REF_FRAME ) && vp9_get_segdata ( seg , segment_id , SEG_LVL_REF_FRAME ) != ( int ) ref_frame ) {
 continue ;
 }
 else if ( ! vp9_segfeature_active ( seg , segment_id , SEG_LVL_REF_FRAME ) ) {
 if ( cpi -> rc . is_src_frame_alt_ref && ( cpi -> oxcf . arnr_max_frames == 0 ) ) continue ;
 }
 mbmi -> tx_size = TX_4X4 ;
 mbmi -> uv_mode = DC_PRED ;
 mbmi -> ref_frame [ 0 ] = ref_frame ;
 mbmi -> ref_frame [ 1 ] = second_ref_frame ;
 mbmi -> interp_filter = cm -> interp_filter == SWITCHABLE ? EIGHTTAP : cm -> interp_filter ;
 x -> skip = 0 ;
 set_ref_ptrs ( cm , xd , ref_frame , second_ref_frame ) ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 i ++ ) {
 xd -> plane [ i ] . pre [ 0 ] = yv12_mb [ ref_frame ] [ i ] ;
 if ( comp_pred ) xd -> plane [ i ] . pre [ 1 ] = yv12_mb [ second_ref_frame ] [ i ] ;
 }
 if ( ref_frame == INTRA_FRAME ) {
 int rate ;
 if ( rd_pick_intra_sub_8x8_y_mode ( cpi , x , & rate , & rate_y , & distortion_y , best_rd ) >= best_rd ) continue ;
 rate2 += rate ;
 rate2 += intra_cost_penalty ;
 distortion2 += distortion_y ;
 if ( rate_uv_intra == INT_MAX ) {
 choose_intra_uv_mode ( cpi , ctx , bsize , TX_4X4 , & rate_uv_intra , & rate_uv_tokenonly , & dist_uv , & skip_uv , & mode_uv ) ;
 }
 rate2 += rate_uv_intra ;
 rate_uv = rate_uv_tokenonly ;
 distortion2 += dist_uv ;
 distortion_uv = dist_uv ;
 mbmi -> uv_mode = mode_uv ;
 }
 else {
 int rate ;
 int64_t distortion ;
 int64_t this_rd_thresh ;
 int64_t tmp_rd , tmp_best_rd = INT64_MAX , tmp_best_rdu = INT64_MAX ;
 int tmp_best_rate = INT_MAX , tmp_best_ratey = INT_MAX ;
 int64_t tmp_best_distortion = INT_MAX , tmp_best_sse , uv_sse ;
 int tmp_best_skippable = 0 ;
 int switchable_filter_index ;
 int_mv * second_ref = comp_pred ? & mbmi -> ref_mvs [ second_ref_frame ] [ 0 ] : NULL ;
 b_mode_info tmp_best_bmodes [ 16 ] ;
 MB_MODE_INFO tmp_best_mbmode ;
 BEST_SEG_INFO bsi [ SWITCHABLE_FILTERS ] ;
 int pred_exists = 0 ;
 int uv_skippable ;
 this_rd_thresh = ( ref_frame == LAST_FRAME ) ? rd_opt -> threshes [ segment_id ] [ bsize ] [ THR_LAST ] : rd_opt -> threshes [ segment_id ] [ bsize ] [ THR_ALTR ] ;
 this_rd_thresh = ( ref_frame == GOLDEN_FRAME ) ? rd_opt -> threshes [ segment_id ] [ bsize ] [ THR_GOLD ] : this_rd_thresh ;
 rd_opt -> mask_filter = 0 ;
 for ( i = 0 ;
 i < SWITCHABLE_FILTER_CONTEXTS ;
 ++ i ) rd_opt -> filter_cache [ i ] = INT64_MAX ;
 if ( cm -> interp_filter != BILINEAR ) {
 tmp_best_filter = EIGHTTAP ;
 if ( x -> source_variance < cpi -> sf . disable_filter_search_var_thresh ) {
 tmp_best_filter = EIGHTTAP ;
 }
 else if ( cpi -> sf . adaptive_pred_interp_filter == 1 && ctx -> pred_interp_filter < SWITCHABLE ) {
 tmp_best_filter = ctx -> pred_interp_filter ;
 }
 else if ( cpi -> sf . adaptive_pred_interp_filter == 2 ) {
 tmp_best_filter = ctx -> pred_interp_filter < SWITCHABLE ? ctx -> pred_interp_filter : 0 ;
 }
 else {
 for ( switchable_filter_index = 0 ;
 switchable_filter_index < SWITCHABLE_FILTERS ;
 ++ switchable_filter_index ) {
 int newbest , rs ;
 int64_t rs_rd ;
 mbmi -> interp_filter = switchable_filter_index ;
 tmp_rd = rd_pick_best_sub8x8_mode ( cpi , x , tile , & mbmi -> ref_mvs [ ref_frame ] [ 0 ] , second_ref , best_yrd , & rate , & rate_y , & distortion , & skippable , & total_sse , ( int ) this_rd_thresh , seg_mvs , bsi , switchable_filter_index , mi_row , mi_col ) ;
 if ( tmp_rd == INT64_MAX ) continue ;
 rs = vp9_get_switchable_rate ( cpi ) ;
 rs_rd = RDCOST ( x -> rdmult , x -> rddiv , rs , 0 ) ;
 rd_opt -> filter_cache [ switchable_filter_index ] = tmp_rd ;
 rd_opt -> filter_cache [ SWITCHABLE_FILTERS ] = MIN ( rd_opt -> filter_cache [ SWITCHABLE_FILTERS ] , tmp_rd + rs_rd ) ;
 if ( cm -> interp_filter == SWITCHABLE ) tmp_rd += rs_rd ;
 rd_opt -> mask_filter = MAX ( rd_opt -> mask_filter , tmp_rd ) ;
 newbest = ( tmp_rd < tmp_best_rd ) ;
 if ( newbest ) {
 tmp_best_filter = mbmi -> interp_filter ;
 tmp_best_rd = tmp_rd ;
 }
 if ( ( newbest && cm -> interp_filter == SWITCHABLE ) || ( mbmi -> interp_filter == cm -> interp_filter && cm -> interp_filter != SWITCHABLE ) ) {
 tmp_best_rdu = tmp_rd ;
 tmp_best_rate = rate ;
 tmp_best_ratey = rate_y ;
 tmp_best_distortion = distortion ;
 tmp_best_sse = total_sse ;
 tmp_best_skippable = skippable ;
 tmp_best_mbmode = * mbmi ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 tmp_best_bmodes [ i ] = xd -> mi [ 0 ] -> bmi [ i ] ;
 x -> zcoeff_blk [ TX_4X4 ] [ i ] = ! x -> plane [ 0 ] . eobs [ i ] ;
 }
 pred_exists = 1 ;
 if ( switchable_filter_index == 0 && cpi -> sf . use_rd_breakout && best_rd < INT64_MAX ) {
 if ( tmp_best_rdu / 2 > best_rd ) {
 tmp_best_filter = mbmi -> interp_filter ;
 tmp_best_rdu = INT64_MAX ;
 break ;
 }
 }
 }
 }
 }
 }
 if ( tmp_best_rdu == INT64_MAX && pred_exists ) continue ;
 mbmi -> interp_filter = ( cm -> interp_filter == SWITCHABLE ? tmp_best_filter : cm -> interp_filter ) ;
 if ( ! pred_exists ) {
 tmp_rd = rd_pick_best_sub8x8_mode ( cpi , x , tile , & mbmi -> ref_mvs [ ref_frame ] [ 0 ] , second_ref , best_yrd , & rate , & rate_y , & distortion , & skippable , & total_sse , ( int ) this_rd_thresh , seg_mvs , bsi , 0 , mi_row , mi_col ) ;
 if ( tmp_rd == INT64_MAX ) continue ;
 }
 else {
 total_sse = tmp_best_sse ;
 rate = tmp_best_rate ;
 rate_y = tmp_best_ratey ;
 distortion = tmp_best_distortion ;
 skippable = tmp_best_skippable ;
 * mbmi = tmp_best_mbmode ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) xd -> mi [ 0 ] -> bmi [ i ] = tmp_best_bmodes [ i ] ;
 }
 rate2 += rate ;
 distortion2 += distortion ;
 if ( cm -> interp_filter == SWITCHABLE ) rate2 += vp9_get_switchable_rate ( cpi ) ;
 if ( ! mode_excluded ) mode_excluded = comp_pred ? cm -> reference_mode == SINGLE_REFERENCE : cm -> reference_mode == COMPOUND_REFERENCE ;
 compmode_cost = vp9_cost_bit ( comp_mode_p , comp_pred ) ;
 tmp_best_rdu = best_rd - MIN ( RDCOST ( x -> rdmult , x -> rddiv , rate2 , distortion2 ) , RDCOST ( x -> rdmult , x -> rddiv , 0 , total_sse ) ) ;
 if ( tmp_best_rdu > 0 ) {
 vp9_build_inter_predictors_sbuv ( & x -> e_mbd , mi_row , mi_col , BLOCK_8X8 ) ;
 super_block_uvrd ( cpi , x , & rate_uv , & distortion_uv , & uv_skippable , & uv_sse , BLOCK_8X8 , tmp_best_rdu ) ;
 if ( rate_uv == INT_MAX ) continue ;
 rate2 += rate_uv ;
 distortion2 += distortion_uv ;
 skippable = skippable && uv_skippable ;
 total_sse += uv_sse ;
 }
 }
 if ( cm -> reference_mode == REFERENCE_MODE_SELECT ) rate2 += compmode_cost ;
 if ( second_ref_frame > INTRA_FRAME ) {
 rate2 += ref_costs_comp [ ref_frame ] ;
 }
 else {
 rate2 += ref_costs_single [ ref_frame ] ;
 }
 if ( ! disable_skip ) {
 if ( ref_frame != INTRA_FRAME && ! xd -> lossless ) {
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
 if ( is_inter_block ( mbmi ) && ! has_second_ref ( mbmi ) && ! mode_excluded && this_rd < best_inter_rd ) {
 best_inter_rd = this_rd ;
 best_inter_ref_frame = ref_frame ;
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
 if ( ! mode_excluded ) {
 int max_plane = MAX_MB_PLANE ;
 best_ref_index = ref_index ;
 if ( ref_frame == INTRA_FRAME ) {
 mbmi -> mv [ 0 ] . as_int = 0 ;
 max_plane = 1 ;
 }
 * returnrate = rate2 ;
 * returndistortion = distortion2 ;
 best_rd = this_rd ;
 best_yrd = best_rd - RDCOST ( x -> rdmult , x -> rddiv , rate_uv , distortion_uv ) ;
 best_mbmode = * mbmi ;
 best_skip2 = this_skip2 ;
 if ( ! x -> select_tx_size ) swap_block_ptr ( x , ctx , 1 , 0 , 0 , max_plane ) ;
 vpx_memcpy ( ctx -> zcoeff_blk , x -> zcoeff_blk [ TX_4X4 ] , sizeof ( uint8_t ) * ctx -> num_4x4_blk ) ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) best_bmodes [ i ] = xd -> mi [ 0 ] -> bmi [ i ] ;
 if ( ( cpi -> sf . mode_search_skip_flags & FLAG_EARLY_TERMINATE ) && ( ref_index > MIN_EARLY_TERM_INDEX ) ) {
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
 if ( ! comp_pred && single_rd < best_pred_rd [ SINGLE_REFERENCE ] ) {
 best_pred_rd [ SINGLE_REFERENCE ] = single_rd ;
 }
 else if ( comp_pred && single_rd < best_pred_rd [ COMPOUND_REFERENCE ] ) {
 best_pred_rd [ COMPOUND_REFERENCE ] = single_rd ;
 }
 if ( hybrid_rd < best_pred_rd [ REFERENCE_MODE_SELECT ] ) best_pred_rd [ REFERENCE_MODE_SELECT ] = hybrid_rd ;
 }
 if ( ! mode_excluded && ! disable_skip && ref_frame != INTRA_FRAME && cm -> interp_filter != BILINEAR ) {
 int64_t ref = rd_opt -> filter_cache [ cm -> interp_filter == SWITCHABLE ? SWITCHABLE_FILTERS : cm -> interp_filter ] ;
 int64_t adj_rd ;
 for ( i = 0 ;
 i < SWITCHABLE_FILTER_CONTEXTS ;
 i ++ ) {
 if ( ref == INT64_MAX ) adj_rd = 0 ;
 else if ( rd_opt -> filter_cache [ i ] == INT64_MAX ) adj_rd = rd_opt -> mask_filter - ref + 10 ;
 else adj_rd = rd_opt -> filter_cache [ i ] - ref ;
 adj_rd += this_rd ;
 best_filter_rd [ i ] = MIN ( best_filter_rd [ i ] , adj_rd ) ;
 }
 }
 if ( early_term ) break ;
 if ( x -> skip && ! comp_pred ) break ;
 }
 if ( best_rd >= best_rd_so_far ) return INT64_MAX ;
 if ( cpi -> sf . use_uv_intra_rd_estimate ) {
 if ( vp9_ref_order [ best_ref_index ] . ref_frame [ 0 ] == INTRA_FRAME ) {
 * mbmi = best_mbmode ;
 rd_pick_intra_sbuv_mode ( cpi , x , ctx , & rate_uv_intra , & rate_uv_tokenonly , & dist_uv , & skip_uv , BLOCK_8X8 , TX_4X4 ) ;
 }
 }
 if ( best_rd == INT64_MAX ) {
 * returnrate = INT_MAX ;
 * returndistortion = INT64_MAX ;
 return best_rd ;
 }
 assert ( ( cm -> interp_filter == SWITCHABLE ) || ( cm -> interp_filter == best_mbmode . interp_filter ) || ! is_inter_block ( & best_mbmode ) ) ;
 update_rd_thresh_fact ( cpi , bsize , best_ref_index ) ;
 * mbmi = best_mbmode ;
 x -> skip |= best_skip2 ;
 if ( ! is_inter_block ( & best_mbmode ) ) {
 for ( i = 0 ;
 i < 4 ;
 i ++ ) xd -> mi [ 0 ] -> bmi [ i ] . as_mode = best_bmodes [ i ] . as_mode ;
 }
 else {
 for ( i = 0 ;
 i < 4 ;
 ++ i ) vpx_memcpy ( & xd -> mi [ 0 ] -> bmi [ i ] , & best_bmodes [ i ] , sizeof ( b_mode_info ) ) ;
 mbmi -> mv [ 0 ] . as_int = xd -> mi [ 0 ] -> bmi [ 3 ] . as_mv [ 0 ] . as_int ;
 mbmi -> mv [ 1 ] . as_int = xd -> mi [ 0 ] -> bmi [ 3 ] . as_mv [ 1 ] . as_int ;
 }
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
 }
 else {
 vp9_zero ( best_filter_diff ) ;
 }
 set_ref_ptrs ( cm , xd , mbmi -> ref_frame [ 0 ] , mbmi -> ref_frame [ 1 ] ) ;
 store_coding_context ( x , ctx , best_ref_index , best_pred_diff , best_tx_diff , best_filter_diff , 0 ) ;
 return best_rd ;
 }
static void update_state ( VP9_COMP * cpi , PICK_MODE_CONTEXT * ctx , int mi_row , int mi_col , BLOCK_SIZE bsize , int output_enabled ) {
 int i , x_idx , y ;
 VP9_COMMON * const cm = & cpi -> common ;
 RD_OPT * const rd_opt = & cpi -> rd ;
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 struct macroblock_plane * const p = x -> plane ;
 struct macroblockd_plane * const pd = xd -> plane ;
 MODE_INFO * mi = & ctx -> mic ;
 MB_MODE_INFO * const mbmi = & xd -> mi [ 0 ] -> mbmi ;
 MODE_INFO * mi_addr = xd -> mi [ 0 ] ;
 const struct segmentation * const seg = & cm -> seg ;
 const int mis = cm -> mi_stride ;
 const int mi_width = num_8x8_blocks_wide_lookup [ bsize ] ;
 const int mi_height = num_8x8_blocks_high_lookup [ bsize ] ;
 int max_plane ;
 assert ( mi -> mbmi . sb_type == bsize ) ;
 * mi_addr = * mi ;
 if ( seg -> enabled && output_enabled ) {
 if ( cpi -> oxcf . aq_mode == COMPLEXITY_AQ ) {
 const uint8_t * const map = seg -> update_map ? cpi -> segmentation_map : cm -> last_frame_seg_map ;
 mi_addr -> mbmi . segment_id = vp9_get_segment_id ( cm , map , bsize , mi_row , mi_col ) ;
 }
 if ( cpi -> oxcf . aq_mode == CYCLIC_REFRESH_AQ ) {
 vp9_cyclic_refresh_update_segment ( cpi , & xd -> mi [ 0 ] -> mbmi , mi_row , mi_col , bsize , 1 ) ;
 }
 }
 max_plane = is_inter_block ( mbmi ) ? MAX_MB_PLANE : 1 ;
 for ( i = 0 ;
 i < max_plane ;
 ++ i ) {
 p [ i ] . coeff = ctx -> coeff_pbuf [ i ] [ 1 ] ;
 p [ i ] . qcoeff = ctx -> qcoeff_pbuf [ i ] [ 1 ] ;
 pd [ i ] . dqcoeff = ctx -> dqcoeff_pbuf [ i ] [ 1 ] ;
 p [ i ] . eobs = ctx -> eobs_pbuf [ i ] [ 1 ] ;
 }
 for ( i = max_plane ;
 i < MAX_MB_PLANE ;
 ++ i ) {
 p [ i ] . coeff = ctx -> coeff_pbuf [ i ] [ 2 ] ;
 p [ i ] . qcoeff = ctx -> qcoeff_pbuf [ i ] [ 2 ] ;
 pd [ i ] . dqcoeff = ctx -> dqcoeff_pbuf [ i ] [ 2 ] ;
 p [ i ] . eobs = ctx -> eobs_pbuf [ i ] [ 2 ] ;
 }
 for ( y = 0 ;
 y < mi_height ;
 y ++ ) for ( x_idx = 0 ;
 x_idx < mi_width ;
 x_idx ++ ) if ( ( xd -> mb_to_right_edge >> ( 3 + MI_SIZE_LOG2 ) ) + mi_width > x_idx && ( xd -> mb_to_bottom_edge >> ( 3 + MI_SIZE_LOG2 ) ) + mi_height > y ) {
 xd -> mi [ x_idx + y * mis ] = mi_addr ;
 }
 if ( cpi -> oxcf . aq_mode ) vp9_init_plane_quantizers ( cpi , x ) ;
 if ( bsize < BLOCK_32X32 ) {
 if ( bsize < BLOCK_16X16 ) ctx -> tx_rd_diff [ ALLOW_16X16 ] = ctx -> tx_rd_diff [ ALLOW_8X8 ] ;
 ctx -> tx_rd_diff [ ALLOW_32X32 ] = ctx -> tx_rd_diff [ ALLOW_16X16 ] ;
 }
 if ( is_inter_block ( mbmi ) && mbmi -> sb_type < BLOCK_8X8 ) {
 mbmi -> mv [ 0 ] . as_int = mi -> bmi [ 3 ] . as_mv [ 0 ] . as_int ;
 mbmi -> mv [ 1 ] . as_int = mi -> bmi [ 3 ] . as_mv [ 1 ] . as_int ;
 }
 x -> skip = ctx -> skip ;
 vpx_memcpy ( x -> zcoeff_blk [ mbmi -> tx_size ] , ctx -> zcoeff_blk , sizeof ( uint8_t ) * ctx -> num_4x4_blk ) ;
 if ( ! output_enabled ) return ;
 if ( ! vp9_segfeature_active ( & cm -> seg , mbmi -> segment_id , SEG_LVL_SKIP ) ) {
 for ( i = 0 ;
 i < TX_MODES ;
 i ++ ) rd_opt -> tx_select_diff [ i ] += ctx -> tx_rd_diff [ i ] ;
 }

 static const int kf_mode_index [ ] = {
 THR_DC , THR_V_PRED , THR_H_PRED , THR_D45_PRED , THR_D135_PRED , THR_D117_PRED , THR_D153_PRED , THR_D207_PRED , THR_D63_PRED , THR_TM , }
 ;
 ++ cpi -> mode_chosen_counts [ kf_mode_index [ mbmi -> mode ] ] ;
 }
 else {
 ++ cpi -> mode_chosen_counts [ ctx -> best_mode_index ] ;
 }

 if ( is_inter_block ( mbmi ) ) {
 vp9_update_mv_count ( cm , xd ) ;
 if ( cm -> interp_filter == SWITCHABLE ) {
 const int ctx = vp9_get_pred_context_switchable_interp ( xd ) ;
 ++ cm -> counts . switchable_interp [ ctx ] [ mbmi -> interp_filter ] ;
 }
 }
 rd_opt -> comp_pred_diff [ SINGLE_REFERENCE ] += ctx -> single_pred_diff ;
 rd_opt -> comp_pred_diff [ COMPOUND_REFERENCE ] += ctx -> comp_pred_diff ;
 rd_opt -> comp_pred_diff [ REFERENCE_MODE_SELECT ] += ctx -> hybrid_pred_diff ;
 for ( i = 0 ;
 i < SWITCHABLE_FILTER_CONTEXTS ;
 ++ i ) rd_opt -> filter_diff [ i ] += ctx -> best_filter_diff [ i ] ;
 }
 }
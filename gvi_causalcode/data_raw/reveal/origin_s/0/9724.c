void vp9_choose_segmap_coding_method ( VP9_COMMON * cm , MACROBLOCKD * xd ) {
 struct segmentation * seg = & cm -> seg ;
 int no_pred_cost ;
 int t_pred_cost = INT_MAX ;
 int i , tile_col , mi_row , mi_col ;
 int temporal_predictor_count [ PREDICTION_PROBS ] [ 2 ] = {
 {
 0 }
 }
 ;
 int no_pred_segcounts [ MAX_SEGMENTS ] = {
 0 }
 ;
 int t_unpred_seg_counts [ MAX_SEGMENTS ] = {
 0 }
 ;
 vp9_prob no_pred_tree [ SEG_TREE_PROBS ] ;
 vp9_prob t_pred_tree [ SEG_TREE_PROBS ] ;
 vp9_prob t_nopred_prob [ PREDICTION_PROBS ] ;
 vpx_memset ( seg -> tree_probs , 255 , sizeof ( seg -> tree_probs ) ) ;
 vpx_memset ( seg -> pred_probs , 255 , sizeof ( seg -> pred_probs ) ) ;
 for ( tile_col = 0 ;
 tile_col < 1 << cm -> log2_tile_cols ;
 tile_col ++ ) {
 TileInfo tile ;
 MODE_INFO * mi_ptr ;
 vp9_tile_init ( & tile , cm , 0 , tile_col ) ;
 mi_ptr = cm -> mi + tile . mi_col_start ;
 for ( mi_row = 0 ;
 mi_row < cm -> mi_rows ;
 mi_row += 8 , mi_ptr += 8 * cm -> mi_stride ) {
 MODE_INFO * mi = mi_ptr ;
 for ( mi_col = tile . mi_col_start ;
 mi_col < tile . mi_col_end ;
 mi_col += 8 , mi += 8 ) count_segs_sb ( cm , xd , & tile , mi , no_pred_segcounts , temporal_predictor_count , t_unpred_seg_counts , mi_row , mi_col , BLOCK_64X64 ) ;
 }
 }
 calc_segtree_probs ( no_pred_segcounts , no_pred_tree ) ;
 no_pred_cost = cost_segmap ( no_pred_segcounts , no_pred_tree ) ;
 if ( ! frame_is_intra_only ( cm ) ) {
 calc_segtree_probs ( t_unpred_seg_counts , t_pred_tree ) ;
 t_pred_cost = cost_segmap ( t_unpred_seg_counts , t_pred_tree ) ;
 for ( i = 0 ;
 i < PREDICTION_PROBS ;
 i ++ ) {
 const int count0 = temporal_predictor_count [ i ] [ 0 ] ;
 const int count1 = temporal_predictor_count [ i ] [ 1 ] ;
 t_nopred_prob [ i ] = get_binary_prob ( count0 , count1 ) ;
 t_pred_cost += count0 * vp9_cost_zero ( t_nopred_prob [ i ] ) + count1 * vp9_cost_one ( t_nopred_prob [ i ] ) ;
 }
 }
 if ( t_pred_cost < no_pred_cost ) {
 seg -> temporal_update = 1 ;
 vpx_memcpy ( seg -> tree_probs , t_pred_tree , sizeof ( t_pred_tree ) ) ;
 vpx_memcpy ( seg -> pred_probs , t_nopred_prob , sizeof ( t_nopred_prob ) ) ;
 }
 else {
 seg -> temporal_update = 0 ;
 vpx_memcpy ( seg -> tree_probs , no_pred_tree , sizeof ( no_pred_tree ) ) ;
 }
 }
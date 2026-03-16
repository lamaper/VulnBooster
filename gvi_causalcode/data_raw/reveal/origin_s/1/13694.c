void vp9_cyclic_refresh_setup ( VP9_COMP * const cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 const RATE_CONTROL * const rc = & cpi -> rc ;
 CYCLIC_REFRESH * const cr = cpi -> cyclic_refresh ;
 struct segmentation * const seg = & cm -> seg ;
 unsigned char * const seg_map = cpi -> segmentation_map ;
 const int apply_cyclic_refresh = apply_cyclic_refresh_bitrate ( cm , rc ) ;
 if ( ! apply_cyclic_refresh || ( cm -> frame_type == KEY_FRAME ) || ( cpi -> svc . temporal_layer_id > 0 ) ) {
 vpx_memset ( seg_map , 0 , cm -> mi_rows * cm -> mi_cols ) ;
 vp9_disable_segmentation ( & cm -> seg ) ;
 if ( cm -> frame_type == KEY_FRAME ) cr -> sb_index = 0 ;
 return ;
 }
 else {
 int qindex_delta = 0 ;
 int i , block_count , bl_index , sb_rows , sb_cols , sbs_in_frame ;
 int xmis , ymis , x , y , qindex2 ;
 const float rate_ratio_qdelta = 2.0 ;
 const double q = vp9_convert_qindex_to_q ( cm -> base_qindex ) ;
 vp9_clear_system_state ( ) ;
 cr -> max_sbs_perframe = 10 ;
 cr -> max_qdelta_perc = 50 ;
 cr -> min_block_size = BLOCK_8X8 ;
 cr -> time_for_refresh = 1 ;
 cr -> thresh_rate_sb = ( rc -> sb64_target_rate * 256 ) >> 2 ;
 cr -> thresh_dist_sb = 8 * ( int ) ( q * q ) ;
 if ( cpi -> sf . use_nonrd_pick_mode ) {
 cr -> thresh_rate_sb = ( rc -> sb64_target_rate * 256 ) >> 3 ;
 cr -> thresh_dist_sb = 4 * ( int ) ( q * q ) ;
 }
 cr -> num_seg_blocks = 0 ;
 vpx_memset ( seg_map , 0 , cm -> mi_rows * cm -> mi_cols ) ;
 vp9_enable_segmentation ( & cm -> seg ) ;
 vp9_clearall_segfeatures ( seg ) ;
 seg -> abs_delta = SEGMENT_DELTADATA ;
 vp9_disable_segfeature ( seg , 0 , SEG_LVL_ALT_Q ) ;
 vp9_enable_segfeature ( seg , 1 , SEG_LVL_ALT_Q ) ;
 qindex_delta = vp9_compute_qdelta_by_rate ( rc , cm -> frame_type , cm -> base_qindex , rate_ratio_qdelta ) ;
 if ( - qindex_delta > cr -> max_qdelta_perc * cm -> base_qindex / 100 ) qindex_delta = - cr -> max_qdelta_perc * cm -> base_qindex / 100 ;
 qindex2 = clamp ( cm -> base_qindex + cm -> y_dc_delta_q + qindex_delta , 0 , MAXQ ) ;
 cr -> rdmult = vp9_compute_rd_mult ( cpi , qindex2 ) ;
 vp9_set_segdata ( seg , 1 , SEG_LVL_ALT_Q , qindex_delta ) ;
 sb_cols = ( cm -> mi_cols + MI_BLOCK_SIZE - 1 ) / MI_BLOCK_SIZE ;
 sb_rows = ( cm -> mi_rows + MI_BLOCK_SIZE - 1 ) / MI_BLOCK_SIZE ;
 sbs_in_frame = sb_cols * sb_rows ;
 block_count = cr -> max_sbs_perframe * sbs_in_frame / 100 ;
 assert ( cr -> sb_index < sbs_in_frame ) ;
 i = cr -> sb_index ;
 do {
 int sum_map = 0 ;
 int sb_row_index = ( i / sb_cols ) ;
 int sb_col_index = i - sb_row_index * sb_cols ;
 int mi_row = sb_row_index * MI_BLOCK_SIZE ;
 int mi_col = sb_col_index * MI_BLOCK_SIZE ;
 assert ( mi_row >= 0 && mi_row < cm -> mi_rows ) ;
 assert ( mi_col >= 0 && mi_col < cm -> mi_cols ) ;
 bl_index = mi_row * cm -> mi_cols + mi_col ;
 xmis = MIN ( cm -> mi_cols - mi_col , num_8x8_blocks_wide_lookup [ BLOCK_64X64 ] ) ;
 ymis = MIN ( cm -> mi_rows - mi_row , num_8x8_blocks_high_lookup [ BLOCK_64X64 ] ) ;
 for ( y = 0 ;
 y < ymis ;
 y ++ ) {
 for ( x = 0 ;
 x < xmis ;
 x ++ ) {
 const int bl_index2 = bl_index + y * cm -> mi_cols + x ;
 if ( cr -> map [ bl_index2 ] == 0 ) {
 seg_map [ bl_index2 ] = 1 ;
 sum_map ++ ;
 }
 else if ( cr -> map [ bl_index2 ] < 0 ) {
 cr -> map [ bl_index2 ] ++ ;
 }
 }
 }
 if ( sum_map > 0 && sum_map < xmis * ymis ) {
 const int new_value = ( sum_map >= xmis * ymis / 2 ) ;
 for ( y = 0 ;
 y < ymis ;
 y ++ ) for ( x = 0 ;
 x < xmis ;
 x ++ ) seg_map [ bl_index + y * cm -> mi_cols + x ] = new_value ;
 }
 i ++ ;
 if ( i == sbs_in_frame ) {
 i = 0 ;
 }
 if ( sum_map >= xmis * ymis / 2 ) block_count -- ;
 }
 while ( block_count && i != cr -> sb_index ) ;
 cr -> sb_index = i ;
 }
 }
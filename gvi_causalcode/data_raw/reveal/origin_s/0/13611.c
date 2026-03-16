void vp9_cyclic_refresh_update_segment ( VP9_COMP * const cpi , MB_MODE_INFO * const mbmi , int mi_row , int mi_col , BLOCK_SIZE bsize , int use_rd ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 CYCLIC_REFRESH * const cr = cpi -> cyclic_refresh ;
 const int bw = num_8x8_blocks_wide_lookup [ bsize ] ;
 const int bh = num_8x8_blocks_high_lookup [ bsize ] ;
 const int xmis = MIN ( cm -> mi_cols - mi_col , bw ) ;
 const int ymis = MIN ( cm -> mi_rows - mi_row , bh ) ;
 const int block_index = mi_row * cm -> mi_cols + mi_col ;
 const int refresh_this_block = cpi -> mb . in_static_area || candidate_refresh_aq ( cr , mbmi , bsize , use_rd ) ;
 int new_map_value = cr -> map [ block_index ] ;
 int x = 0 ;
 int y = 0 ;
 if ( mbmi -> segment_id > 0 && ! refresh_this_block ) mbmi -> segment_id = 0 ;
 if ( mbmi -> segment_id == 1 ) {
 new_map_value = - cr -> time_for_refresh ;
 }
 else if ( refresh_this_block ) {
 if ( cr -> map [ block_index ] == 1 ) new_map_value = 0 ;
 }
 else {
 new_map_value = 1 ;
 }
 for ( y = 0 ;
 y < ymis ;
 y ++ ) for ( x = 0 ;
 x < xmis ;
 x ++ ) {
 cr -> map [ block_index + y * cm -> mi_cols + x ] = new_map_value ;
 cpi -> segmentation_map [ block_index + y * cm -> mi_cols + x ] = mbmi -> segment_id ;
 }
 if ( mbmi -> segment_id ) cr -> num_seg_blocks += xmis * ymis ;
 }
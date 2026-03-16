static MB_MODE_INFO * set_offsets ( VP9_COMMON * const cm , MACROBLOCKD * const xd , const TileInfo * const tile , BLOCK_SIZE bsize , int mi_row , int mi_col ) {
 const int bw = num_8x8_blocks_wide_lookup [ bsize ] ;
 const int bh = num_8x8_blocks_high_lookup [ bsize ] ;
 const int x_mis = MIN ( bw , cm -> mi_cols - mi_col ) ;
 const int y_mis = MIN ( bh , cm -> mi_rows - mi_row ) ;
 const int offset = mi_row * cm -> mi_stride + mi_col ;
 int x , y ;
 xd -> mi = cm -> mi_grid_visible + offset ;
 xd -> mi [ 0 ] = & cm -> mi [ offset ] ;
 xd -> mi [ 0 ] -> mbmi . sb_type = bsize ;
 for ( y = 0 ;
 y < y_mis ;
 ++ y ) for ( x = ! y ;
 x < x_mis ;
 ++ x ) xd -> mi [ y * cm -> mi_stride + x ] = xd -> mi [ 0 ] ;
 set_skip_context ( xd , mi_row , mi_col ) ;
 set_mi_row_col ( xd , tile , mi_row , bh , mi_col , bw , cm -> mi_rows , cm -> mi_cols ) ;
 vp9_setup_dst_planes ( xd -> plane , get_frame_new_buffer ( cm ) , mi_row , mi_col ) ;
 return & xd -> mi [ 0 ] -> mbmi ;
 }
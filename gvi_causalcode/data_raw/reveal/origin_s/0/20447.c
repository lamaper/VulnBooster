void vp9_loop_filter_rows ( YV12_BUFFER_CONFIG * frame_buffer , VP9_COMMON * cm , struct macroblockd_plane planes [ MAX_MB_PLANE ] , int start , int stop , int y_only ) {
 const int num_planes = y_only ? 1 : MAX_MB_PLANE ;
 const int use_420 = y_only || ( planes [ 1 ] . subsampling_y == 1 && planes [ 1 ] . subsampling_x == 1 ) ;
 LOOP_FILTER_MASK lfm ;
 int mi_row , mi_col ;
 for ( mi_row = start ;
 mi_row < stop ;
 mi_row += MI_BLOCK_SIZE ) {
 MODE_INFO * mi = cm -> mi + mi_row * cm -> mi_stride ;
 for ( mi_col = 0 ;
 mi_col < cm -> mi_cols ;
 mi_col += MI_BLOCK_SIZE ) {
 int plane ;
 vp9_setup_dst_planes ( planes , frame_buffer , mi_row , mi_col ) ;
 if ( use_420 ) vp9_setup_mask ( cm , mi_row , mi_col , mi + mi_col , cm -> mi_stride , & lfm ) ;
 for ( plane = 0 ;
 plane < num_planes ;
 ++ plane ) {
 if ( use_420 ) vp9_filter_block_plane ( cm , & planes [ plane ] , mi_row , & lfm ) ;
 else filter_block_plane_non420 ( cm , & planes [ plane ] , mi + mi_col , mi_row , mi_col ) ;
 }
 }
 }
 }
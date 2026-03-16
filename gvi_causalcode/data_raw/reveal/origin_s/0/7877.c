static int tile_worker_hook ( TileWorkerData * const tile_data , const TileInfo * const tile ) {
 int mi_row , mi_col ;
 for ( mi_row = tile -> mi_row_start ;
 mi_row < tile -> mi_row_end ;
 mi_row += MI_BLOCK_SIZE ) {
 vp9_zero ( tile_data -> xd . left_context ) ;
 vp9_zero ( tile_data -> xd . left_seg_context ) ;
 for ( mi_col = tile -> mi_col_start ;
 mi_col < tile -> mi_col_end ;
 mi_col += MI_BLOCK_SIZE ) {
 decode_partition ( tile_data -> cm , & tile_data -> xd , tile , mi_row , mi_col , & tile_data -> bit_reader , BLOCK_64X64 ) ;
 }
 }
 return ! tile_data -> xd . corrupted ;
 }
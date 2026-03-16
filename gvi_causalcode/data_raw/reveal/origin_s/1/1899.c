static void auto_partition_range ( VP9_COMP * cpi , const TileInfo * const tile , int mi_row , int mi_col , BLOCK_SIZE * min_block_size , BLOCK_SIZE * max_block_size ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCKD * const xd = & cpi -> mb . e_mbd ;
 MODE_INFO * * mi_8x8 = xd -> mi ;
 const int left_in_image = xd -> left_available && mi_8x8 [ - 1 ] ;
 const int above_in_image = xd -> up_available && mi_8x8 [ - xd -> mi_stride ] ;
 int row8x8_remaining = tile -> mi_row_end - mi_row ;
 int col8x8_remaining = tile -> mi_col_end - mi_col ;
 int bh , bw ;
 BLOCK_SIZE min_size = BLOCK_32X32 ;
 BLOCK_SIZE max_size = BLOCK_8X8 ;
 int bsl = mi_width_log2 ( BLOCK_64X64 ) ;
 const int search_range_ctrl = ( ( ( mi_row + mi_col ) >> bsl ) + get_chessboard_index ( cm -> current_video_frame ) ) & 0x1 ;
 if ( search_range_ctrl && ( left_in_image || above_in_image || cm -> frame_type != KEY_FRAME ) ) {
 int block ;
 MODE_INFO * * mi ;
 BLOCK_SIZE sb_type ;
 if ( left_in_image ) {
 MODE_INFO * cur_mi ;
 mi = & mi_8x8 [ - 1 ] ;
 for ( block = 0 ;
 block < MI_BLOCK_SIZE ;
 ++ block ) {
 cur_mi = mi [ block * xd -> mi_stride ] ;
 sb_type = cur_mi ? cur_mi -> mbmi . sb_type : 0 ;
 min_size = MIN ( min_size , sb_type ) ;
 max_size = MAX ( max_size , sb_type ) ;
 }
 }
 if ( above_in_image ) {
 mi = & mi_8x8 [ - xd -> mi_stride * MI_BLOCK_SIZE ] ;
 for ( block = 0 ;
 block < MI_BLOCK_SIZE ;
 ++ block ) {
 sb_type = mi [ block ] ? mi [ block ] -> mbmi . sb_type : 0 ;
 min_size = MIN ( min_size , sb_type ) ;
 max_size = MAX ( max_size , sb_type ) ;
 }
 }
 min_size = min_partition_size [ min_size ] ;
 max_size = find_partition_size ( max_size , row8x8_remaining , col8x8_remaining , & bh , & bw ) ;
 min_size = MIN ( min_size , max_size ) ;
 min_size = MAX ( min_size , BLOCK_8X8 ) ;
 max_size = MIN ( max_size , BLOCK_32X32 ) ;
 }
 else {
 min_size = BLOCK_8X8 ;
 max_size = BLOCK_32X32 ;
 }
 * min_block_size = min_size ;
 * max_block_size = max_size ;
 }
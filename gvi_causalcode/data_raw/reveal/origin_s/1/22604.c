static void set_fixed_partitioning ( VP9_COMP * cpi , const TileInfo * const tile , MODE_INFO * * mi_8x8 , int mi_row , int mi_col , BLOCK_SIZE bsize ) {
 VP9_COMMON * const cm = & cpi -> common ;
 const int mis = cm -> mi_stride ;
 const int row8x8_remaining = tile -> mi_row_end - mi_row ;
 const int col8x8_remaining = tile -> mi_col_end - mi_col ;
 int block_row , block_col ;
 MODE_INFO * mi_upper_left = cm -> mi + mi_row * mis + mi_col ;
 int bh = num_8x8_blocks_high_lookup [ bsize ] ;
 int bw = num_8x8_blocks_wide_lookup [ bsize ] ;
 assert ( ( row8x8_remaining > 0 ) && ( col8x8_remaining > 0 ) ) ;
 if ( ( col8x8_remaining >= MI_BLOCK_SIZE ) && ( row8x8_remaining >= MI_BLOCK_SIZE ) ) {
 for ( block_row = 0 ;
 block_row < MI_BLOCK_SIZE ;
 block_row += bh ) {
 for ( block_col = 0 ;
 block_col < MI_BLOCK_SIZE ;
 block_col += bw ) {
 int index = block_row * mis + block_col ;
 mi_8x8 [ index ] = mi_upper_left + index ;
 mi_8x8 [ index ] -> mbmi . sb_type = bsize ;
 }
 }
 }
 else {
 set_partial_b64x64_partition ( mi_upper_left , mis , bh , bw , row8x8_remaining , col8x8_remaining , bsize , mi_8x8 ) ;
 }
 }
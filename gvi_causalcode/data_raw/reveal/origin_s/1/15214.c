static void constrain_copy_partitioning ( VP9_COMP * const cpi , const TileInfo * const tile , MODE_INFO * * mi_8x8 , MODE_INFO * * prev_mi_8x8 , int mi_row , int mi_col , BLOCK_SIZE bsize ) {
 VP9_COMMON * const cm = & cpi -> common ;
 const int mis = cm -> mi_stride ;
 const int row8x8_remaining = tile -> mi_row_end - mi_row ;
 const int col8x8_remaining = tile -> mi_col_end - mi_col ;
 MODE_INFO * const mi_upper_left = cm -> mi + mi_row * mis + mi_col ;
 const int bh = num_8x8_blocks_high_lookup [ bsize ] ;
 const int bw = num_8x8_blocks_wide_lookup [ bsize ] ;
 int block_row , block_col ;
 assert ( ( row8x8_remaining > 0 ) && ( col8x8_remaining > 0 ) ) ;
 if ( ( col8x8_remaining >= MI_BLOCK_SIZE ) && ( row8x8_remaining >= MI_BLOCK_SIZE ) ) {
 for ( block_row = 0 ;
 block_row < MI_BLOCK_SIZE ;
 block_row += bh ) {
 for ( block_col = 0 ;
 block_col < MI_BLOCK_SIZE ;
 block_col += bw ) {
 const int index = block_row * mis + block_col ;
 MODE_INFO * prev_mi = prev_mi_8x8 [ index ] ;
 const BLOCK_SIZE sb_type = prev_mi ? prev_mi -> mbmi . sb_type : 0 ;
 if ( prev_mi && sb_type <= bsize ) {
 int block_row2 , block_col2 ;
 for ( block_row2 = 0 ;
 block_row2 < bh ;
 ++ block_row2 ) {
 for ( block_col2 = 0 ;
 block_col2 < bw ;
 ++ block_col2 ) {
 const int index2 = ( block_row + block_row2 ) * mis + block_col + block_col2 ;
 prev_mi = prev_mi_8x8 [ index2 ] ;
 if ( prev_mi ) {
 const ptrdiff_t offset = prev_mi - cm -> prev_mi ;
 mi_8x8 [ index2 ] = cm -> mi + offset ;
 mi_8x8 [ index2 ] -> mbmi . sb_type = prev_mi -> mbmi . sb_type ;
 }
 }
 }
 }
 else {
 mi_8x8 [ index ] = mi_upper_left + index ;
 mi_8x8 [ index ] -> mbmi . sb_type = bsize ;
 }
 }
 }
 }
 else {
 copy_partitioning ( cm , mi_8x8 , prev_mi_8x8 ) ;
 }
 }
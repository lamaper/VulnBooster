static void set_source_var_based_partition ( VP9_COMP * cpi , const TileInfo * const tile , MODE_INFO * mi_8x8 , int mi_row , int mi_col ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCK * const x = & cpi -> mb ;
 const int mis = cm -> mi_stride ;
 const int row8x8_remaining = tile -> mi_row_end - mi_row ;
 const int col8x8_remaining = tile -> mi_col_end - mi_col ;
 MODE_INFO * mi_upper_left = cm -> mi + mi_row * mis + mi_col ;
 vp9_setup_src_planes ( x , cpi -> Source , mi_row , mi_col ) ;
 assert ( ( row8x8_remaining > 0 ) && ( col8x8_remaining > 0 ) ) ;
 if ( ( col8x8_remaining >= MI_BLOCK_SIZE ) && ( row8x8_remaining >= MI_BLOCK_SIZE ) ) {
 int i , j ;
 int index ;
 diff d32 [ 4 ] ;
 const int offset = ( mi_row >> 1 ) * cm -> mb_cols + ( mi_col >> 1 ) ;
 int is_larger_better = 0 ;
 int use32x32 = 0 ;
 unsigned int thr = cpi -> source_var_thresh ;
 vpx_memset ( d32 , 0 , 4 * sizeof ( diff ) ) ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 diff * d16 [ 4 ] ;
 for ( j = 0 ;
 j < 4 ;
 j ++ ) {
 int b_mi_row = coord_lookup [ i * 4 + j ] . row ;
 int b_mi_col = coord_lookup [ i * 4 + j ] . col ;
 int boffset = b_mi_row / 2 * cm -> mb_cols + b_mi_col / 2 ;
 d16 [ j ] = cpi -> source_diff_var + offset + boffset ;
 index = b_mi_row * mis + b_mi_col ;
 mi_8x8 [ index ] . src_mi = mi_upper_left + index ;
 mi_8x8 [ index ] . src_mi -> mbmi . sb_type = BLOCK_16X16 ;
 }
 is_larger_better = ( d16 [ 0 ] -> var < thr ) && ( d16 [ 1 ] -> var < thr ) && ( d16 [ 2 ] -> var < thr ) && ( d16 [ 3 ] -> var < thr ) ;
 if ( is_larger_better ) {
 use32x32 += 1 ;
 for ( j = 0 ;
 j < 4 ;
 j ++ ) {
 d32 [ i ] . sse += d16 [ j ] -> sse ;
 d32 [ i ] . sum += d16 [ j ] -> sum ;
 }
 d32 [ i ] . var = d32 [ i ] . sse - ( ( ( int64_t ) d32 [ i ] . sum * d32 [ i ] . sum ) >> 10 ) ;
 index = coord_lookup [ i * 4 ] . row * mis + coord_lookup [ i * 4 ] . col ;
 mi_8x8 [ index ] . src_mi = mi_upper_left + index ;
 mi_8x8 [ index ] . src_mi -> mbmi . sb_type = BLOCK_32X32 ;
 }
 }
 if ( use32x32 == 4 ) {
 thr <<= 1 ;
 is_larger_better = ( d32 [ 0 ] . var < thr ) && ( d32 [ 1 ] . var < thr ) && ( d32 [ 2 ] . var < thr ) && ( d32 [ 3 ] . var < thr ) ;
 if ( is_larger_better ) {
 mi_8x8 [ 0 ] . src_mi = mi_upper_left ;
 mi_8x8 [ 0 ] . src_mi -> mbmi . sb_type = BLOCK_64X64 ;
 }
 }
 }
 else {
 int bh = num_8x8_blocks_high_lookup [ BLOCK_16X16 ] ;
 int bw = num_8x8_blocks_wide_lookup [ BLOCK_16X16 ] ;
 set_partial_b64x64_partition ( mi_upper_left , mis , bh , bw , row8x8_remaining , col8x8_remaining , BLOCK_16X16 , mi_8x8 ) ;
 }
 }
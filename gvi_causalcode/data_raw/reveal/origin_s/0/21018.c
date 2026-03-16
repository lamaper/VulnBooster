static void set_partition_range ( VP9_COMMON * cm , MACROBLOCKD * xd , int mi_row , int mi_col , BLOCK_SIZE bsize , BLOCK_SIZE * min_bs , BLOCK_SIZE * max_bs ) {
 int mi_width = num_8x8_blocks_wide_lookup [ bsize ] ;
 int mi_height = num_8x8_blocks_high_lookup [ bsize ] ;
 int idx , idy ;
 MODE_INFO * mi ;
 const int idx_str = cm -> mi_stride * mi_row + mi_col ;
 MODE_INFO * prev_mi = ( cm -> prev_mip + cm -> mi_stride + 1 + idx_str ) -> src_mi ;
 BLOCK_SIZE bs , min_size , max_size ;
 min_size = BLOCK_64X64 ;
 max_size = BLOCK_4X4 ;
 if ( prev_mi ) {
 for ( idy = 0 ;
 idy < mi_height ;
 ++ idy ) {
 for ( idx = 0 ;
 idx < mi_width ;
 ++ idx ) {
 mi = prev_mi [ idy * cm -> mi_stride + idx ] . src_mi ;
 bs = mi ? mi -> mbmi . sb_type : bsize ;
 min_size = MIN ( min_size , bs ) ;
 max_size = MAX ( max_size , bs ) ;
 }
 }
 }
 if ( xd -> left_available ) {
 for ( idy = 0 ;
 idy < mi_height ;
 ++ idy ) {
 mi = xd -> mi [ idy * cm -> mi_stride - 1 ] . src_mi ;
 bs = mi ? mi -> mbmi . sb_type : bsize ;
 min_size = MIN ( min_size , bs ) ;
 max_size = MAX ( max_size , bs ) ;
 }
 }
 if ( xd -> up_available ) {
 for ( idx = 0 ;
 idx < mi_width ;
 ++ idx ) {
 mi = xd -> mi [ idx - cm -> mi_stride ] . src_mi ;
 bs = mi ? mi -> mbmi . sb_type : bsize ;
 min_size = MIN ( min_size , bs ) ;
 max_size = MAX ( max_size , bs ) ;
 }
 }
 if ( min_size == max_size ) {
 min_size = min_partition_size [ min_size ] ;
 max_size = max_partition_size [ max_size ] ;
 }
 * min_bs = min_size ;
 * max_bs = max_size ;
 }
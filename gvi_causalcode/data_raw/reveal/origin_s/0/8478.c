static void rd_auto_partition_range ( VP9_COMP * cpi , const TileInfo * const tile , int mi_row , int mi_col , BLOCK_SIZE * min_block_size , BLOCK_SIZE * max_block_size ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCKD * const xd = & cpi -> mb . e_mbd ;
 MODE_INFO * mi = xd -> mi [ 0 ] . src_mi ;
 const int left_in_image = xd -> left_available && mi [ - 1 ] . src_mi ;
 const int above_in_image = xd -> up_available && mi [ - xd -> mi_stride ] . src_mi ;
 const int row8x8_remaining = tile -> mi_row_end - mi_row ;
 const int col8x8_remaining = tile -> mi_col_end - mi_col ;
 int bh , bw ;
 BLOCK_SIZE min_size = BLOCK_4X4 ;
 BLOCK_SIZE max_size = BLOCK_64X64 ;
 int i = 0 ;
 int bs_hist [ BLOCK_SIZES ] = {
 0 }
 ;
 if ( left_in_image || above_in_image || cm -> frame_type != KEY_FRAME ) {
 min_size = BLOCK_64X64 ;
 max_size = BLOCK_4X4 ;
 if ( cm -> frame_type != KEY_FRAME ) {
 MODE_INFO * prev_mi = cm -> prev_mip + cm -> mi_stride + 1 + mi_row * xd -> mi_stride + mi_col ;
 get_sb_partition_size_range ( xd , prev_mi , & min_size , & max_size , bs_hist ) ;
 }
 if ( left_in_image ) {
 MODE_INFO * left_sb64_mi = mi [ - MI_BLOCK_SIZE ] . src_mi ;
 get_sb_partition_size_range ( xd , left_sb64_mi , & min_size , & max_size , bs_hist ) ;
 }
 if ( above_in_image ) {
 MODE_INFO * above_sb64_mi = mi [ - xd -> mi_stride * MI_BLOCK_SIZE ] . src_mi ;
 get_sb_partition_size_range ( xd , above_sb64_mi , & min_size , & max_size , bs_hist ) ;
 }
 if ( cpi -> sf . auto_min_max_partition_size == RELAXED_NEIGHBORING_MIN_MAX ) {
 min_size = min_partition_size [ min_size ] ;
 max_size = max_partition_size [ max_size ] ;
 }
 else if ( cpi -> sf . auto_min_max_partition_size == CONSTRAIN_NEIGHBORING_MIN_MAX ) {
 int sum = 0 ;
 int first_moment = 0 ;
 int second_moment = 0 ;
 int var_unnormalized = 0 ;
 for ( i = 0 ;
 i < BLOCK_SIZES ;
 i ++ ) {
 sum += bs_hist [ i ] ;
 first_moment += bs_hist [ i ] * i ;
 second_moment += bs_hist [ i ] * i * i ;
 }
 var_unnormalized = second_moment - first_moment * first_moment / sum ;
 if ( var_unnormalized <= 4 * sum ) {
 int mean = first_moment / sum ;
 min_size = min_partition_size [ mean ] ;
 max_size = max_partition_size [ mean ] ;
 }
 else {
 min_size = min_partition_size [ min_size ] ;
 max_size = max_partition_size [ max_size ] ;
 }
 }
 }
 max_size = find_partition_size ( max_size , row8x8_remaining , col8x8_remaining , & bh , & bw ) ;
 min_size = MIN ( min_size , max_size ) ;
 if ( cpi -> sf . use_square_partition_only && next_square_size [ max_size ] < min_size ) {
 min_size = next_square_size [ max_size ] ;
 }
 * min_block_size = min_size ;
 * max_block_size = max_size ;
 }
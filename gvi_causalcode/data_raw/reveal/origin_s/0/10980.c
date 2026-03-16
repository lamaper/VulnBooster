static void rd_use_partition ( VP9_COMP * cpi , const TileInfo * const tile , MODE_INFO * mi_8x8 , TOKENEXTRA * * tp , int mi_row , int mi_col , BLOCK_SIZE bsize , int * rate , int64_t * dist , int do_recon , PC_TREE * pc_tree ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 const int mis = cm -> mi_stride ;
 const int bsl = b_width_log2 ( bsize ) ;
 const int mi_step = num_4x4_blocks_wide_lookup [ bsize ] / 2 ;
 const int bss = ( 1 << bsl ) / 4 ;
 int i , pl ;
 PARTITION_TYPE partition = PARTITION_NONE ;
 BLOCK_SIZE subsize ;
 ENTROPY_CONTEXT l [ 16 * MAX_MB_PLANE ] , a [ 16 * MAX_MB_PLANE ] ;
 PARTITION_CONTEXT sl [ 8 ] , sa [ 8 ] ;
 int last_part_rate = INT_MAX ;
 int64_t last_part_dist = INT64_MAX ;
 int64_t last_part_rd = INT64_MAX ;
 int none_rate = INT_MAX ;
 int64_t none_dist = INT64_MAX ;
 int64_t none_rd = INT64_MAX ;
 int chosen_rate = INT_MAX ;
 int64_t chosen_dist = INT64_MAX ;
 int64_t chosen_rd = INT64_MAX ;
 BLOCK_SIZE sub_subsize = BLOCK_4X4 ;
 int splits_below = 0 ;
 BLOCK_SIZE bs_type = mi_8x8 [ 0 ] . src_mi -> mbmi . sb_type ;
 int do_partition_search = 1 ;
 PICK_MODE_CONTEXT * ctx = & pc_tree -> none ;
 if ( mi_row >= cm -> mi_rows || mi_col >= cm -> mi_cols ) return ;
 assert ( num_4x4_blocks_wide_lookup [ bsize ] == num_4x4_blocks_high_lookup [ bsize ] ) ;
 partition = partition_lookup [ bsl ] [ bs_type ] ;
 subsize = get_subsize ( bsize , partition ) ;
 pc_tree -> partitioning = partition ;
 save_context ( cpi , mi_row , mi_col , a , l , sa , sl , bsize ) ;
 if ( bsize == BLOCK_16X16 && cpi -> oxcf . aq_mode ) {
 set_offsets ( cpi , tile , mi_row , mi_col , bsize ) ;
 x -> mb_energy = vp9_block_energy ( cpi , x , bsize ) ;
 }
 if ( do_partition_search && cpi -> sf . partition_search_type == SEARCH_PARTITION && cpi -> sf . adjust_partitioning_from_last_frame ) {
 if ( partition == PARTITION_SPLIT && subsize > BLOCK_8X8 ) {
 sub_subsize = get_subsize ( subsize , PARTITION_SPLIT ) ;
 splits_below = 1 ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 int jj = i >> 1 , ii = i & 0x01 ;
 MODE_INFO * this_mi = mi_8x8 [ jj * bss * mis + ii * bss ] . src_mi ;
 if ( this_mi && this_mi -> mbmi . sb_type >= sub_subsize ) {
 splits_below = 0 ;
 }
 }
 }
 if ( partition != PARTITION_NONE && ! splits_below && mi_row + ( mi_step >> 1 ) < cm -> mi_rows && mi_col + ( mi_step >> 1 ) < cm -> mi_cols ) {
 pc_tree -> partitioning = PARTITION_NONE ;
 rd_pick_sb_modes ( cpi , tile , mi_row , mi_col , & none_rate , & none_dist , bsize , ctx , INT64_MAX , 0 ) ;
 pl = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 if ( none_rate < INT_MAX ) {
 none_rate += cpi -> partition_cost [ pl ] [ PARTITION_NONE ] ;
 none_rd = RDCOST ( x -> rdmult , x -> rddiv , none_rate , none_dist ) ;
 }
 restore_context ( cpi , mi_row , mi_col , a , l , sa , sl , bsize ) ;
 mi_8x8 [ 0 ] . src_mi -> mbmi . sb_type = bs_type ;
 pc_tree -> partitioning = partition ;
 }
 }
 switch ( partition ) {
 case PARTITION_NONE : rd_pick_sb_modes ( cpi , tile , mi_row , mi_col , & last_part_rate , & last_part_dist , bsize , ctx , INT64_MAX , 0 ) ;
 break ;
 case PARTITION_HORZ : rd_pick_sb_modes ( cpi , tile , mi_row , mi_col , & last_part_rate , & last_part_dist , subsize , & pc_tree -> horizontal [ 0 ] , INT64_MAX , 0 ) ;
 if ( last_part_rate != INT_MAX && bsize >= BLOCK_8X8 && mi_row + ( mi_step >> 1 ) < cm -> mi_rows ) {
 int rt = 0 ;
 int64_t dt = 0 ;
 PICK_MODE_CONTEXT * ctx = & pc_tree -> horizontal [ 0 ] ;
 update_state ( cpi , ctx , mi_row , mi_col , subsize , 0 ) ;
 encode_superblock ( cpi , tp , 0 , mi_row , mi_col , subsize , ctx ) ;
 rd_pick_sb_modes ( cpi , tile , mi_row + ( mi_step >> 1 ) , mi_col , & rt , & dt , subsize , & pc_tree -> horizontal [ 1 ] , INT64_MAX , 1 ) ;
 if ( rt == INT_MAX || dt == INT64_MAX ) {
 last_part_rate = INT_MAX ;
 last_part_dist = INT64_MAX ;
 break ;
 }
 last_part_rate += rt ;
 last_part_dist += dt ;
 }
 break ;
 case PARTITION_VERT : rd_pick_sb_modes ( cpi , tile , mi_row , mi_col , & last_part_rate , & last_part_dist , subsize , & pc_tree -> vertical [ 0 ] , INT64_MAX , 0 ) ;
 if ( last_part_rate != INT_MAX && bsize >= BLOCK_8X8 && mi_col + ( mi_step >> 1 ) < cm -> mi_cols ) {
 int rt = 0 ;
 int64_t dt = 0 ;
 PICK_MODE_CONTEXT * ctx = & pc_tree -> vertical [ 0 ] ;
 update_state ( cpi , ctx , mi_row , mi_col , subsize , 0 ) ;
 encode_superblock ( cpi , tp , 0 , mi_row , mi_col , subsize , ctx ) ;
 rd_pick_sb_modes ( cpi , tile , mi_row , mi_col + ( mi_step >> 1 ) , & rt , & dt , subsize , & pc_tree -> vertical [ bsize > BLOCK_8X8 ] , INT64_MAX , 1 ) ;
 if ( rt == INT_MAX || dt == INT64_MAX ) {
 last_part_rate = INT_MAX ;
 last_part_dist = INT64_MAX ;
 break ;
 }
 last_part_rate += rt ;
 last_part_dist += dt ;
 }
 break ;
 case PARTITION_SPLIT : if ( bsize == BLOCK_8X8 ) {
 rd_pick_sb_modes ( cpi , tile , mi_row , mi_col , & last_part_rate , & last_part_dist , subsize , pc_tree -> leaf_split [ 0 ] , INT64_MAX , 0 ) ;
 break ;
 }
 last_part_rate = 0 ;
 last_part_dist = 0 ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 int x_idx = ( i & 1 ) * ( mi_step >> 1 ) ;
 int y_idx = ( i >> 1 ) * ( mi_step >> 1 ) ;
 int jj = i >> 1 , ii = i & 0x01 ;
 int rt ;
 int64_t dt ;
 if ( ( mi_row + y_idx >= cm -> mi_rows ) || ( mi_col + x_idx >= cm -> mi_cols ) ) continue ;
 rd_use_partition ( cpi , tile , mi_8x8 + jj * bss * mis + ii * bss , tp , mi_row + y_idx , mi_col + x_idx , subsize , & rt , & dt , i != 3 , pc_tree -> split [ i ] ) ;
 if ( rt == INT_MAX || dt == INT64_MAX ) {
 last_part_rate = INT_MAX ;
 last_part_dist = INT64_MAX ;
 break ;
 }
 last_part_rate += rt ;
 last_part_dist += dt ;
 }
 break ;
 default : assert ( 0 ) ;
 break ;
 }
 pl = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 if ( last_part_rate < INT_MAX ) {
 last_part_rate += cpi -> partition_cost [ pl ] [ partition ] ;
 last_part_rd = RDCOST ( x -> rdmult , x -> rddiv , last_part_rate , last_part_dist ) ;
 }
 if ( do_partition_search && cpi -> sf . adjust_partitioning_from_last_frame && cpi -> sf . partition_search_type == SEARCH_PARTITION && partition != PARTITION_SPLIT && bsize > BLOCK_8X8 && ( mi_row + mi_step < cm -> mi_rows || mi_row + ( mi_step >> 1 ) == cm -> mi_rows ) && ( mi_col + mi_step < cm -> mi_cols || mi_col + ( mi_step >> 1 ) == cm -> mi_cols ) ) {
 BLOCK_SIZE split_subsize = get_subsize ( bsize , PARTITION_SPLIT ) ;
 chosen_rate = 0 ;
 chosen_dist = 0 ;
 restore_context ( cpi , mi_row , mi_col , a , l , sa , sl , bsize ) ;
 pc_tree -> partitioning = PARTITION_SPLIT ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 int x_idx = ( i & 1 ) * ( mi_step >> 1 ) ;
 int y_idx = ( i >> 1 ) * ( mi_step >> 1 ) ;
 int rt = 0 ;
 int64_t dt = 0 ;
 ENTROPY_CONTEXT l [ 16 * MAX_MB_PLANE ] , a [ 16 * MAX_MB_PLANE ] ;
 PARTITION_CONTEXT sl [ 8 ] , sa [ 8 ] ;
 if ( ( mi_row + y_idx >= cm -> mi_rows ) || ( mi_col + x_idx >= cm -> mi_cols ) ) continue ;
 save_context ( cpi , mi_row , mi_col , a , l , sa , sl , bsize ) ;
 pc_tree -> split [ i ] -> partitioning = PARTITION_NONE ;
 rd_pick_sb_modes ( cpi , tile , mi_row + y_idx , mi_col + x_idx , & rt , & dt , split_subsize , & pc_tree -> split [ i ] -> none , INT64_MAX , i ) ;
 restore_context ( cpi , mi_row , mi_col , a , l , sa , sl , bsize ) ;
 if ( rt == INT_MAX || dt == INT64_MAX ) {
 chosen_rate = INT_MAX ;
 chosen_dist = INT64_MAX ;
 break ;
 }
 chosen_rate += rt ;
 chosen_dist += dt ;
 if ( i != 3 ) encode_sb ( cpi , tile , tp , mi_row + y_idx , mi_col + x_idx , 0 , split_subsize , pc_tree -> split [ i ] ) ;
 pl = partition_plane_context ( xd , mi_row + y_idx , mi_col + x_idx , split_subsize ) ;
 chosen_rate += cpi -> partition_cost [ pl ] [ PARTITION_NONE ] ;
 }
 pl = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 if ( chosen_rate < INT_MAX ) {
 chosen_rate += cpi -> partition_cost [ pl ] [ PARTITION_SPLIT ] ;
 chosen_rd = RDCOST ( x -> rdmult , x -> rddiv , chosen_rate , chosen_dist ) ;
 }
 }
 if ( last_part_rd < chosen_rd ) {
 mi_8x8 [ 0 ] . src_mi -> mbmi . sb_type = bsize ;
 if ( bsize >= BLOCK_8X8 ) pc_tree -> partitioning = partition ;
 chosen_rate = last_part_rate ;
 chosen_dist = last_part_dist ;
 chosen_rd = last_part_rd ;
 }
 if ( none_rd < chosen_rd ) {
 if ( bsize >= BLOCK_8X8 ) pc_tree -> partitioning = PARTITION_NONE ;
 chosen_rate = none_rate ;
 chosen_dist = none_dist ;
 }
 restore_context ( cpi , mi_row , mi_col , a , l , sa , sl , bsize ) ;
 if ( bsize == BLOCK_64X64 ) assert ( chosen_rate < INT_MAX && chosen_dist < INT64_MAX ) ;
 if ( do_recon ) {
 int output_enabled = ( bsize == BLOCK_64X64 ) ;
 if ( ( cpi -> oxcf . aq_mode == COMPLEXITY_AQ ) && cm -> seg . update_map ) {
 vp9_select_in_frame_q_segment ( cpi , mi_row , mi_col , output_enabled , chosen_rate ) ;
 }
 if ( cpi -> oxcf . aq_mode == CYCLIC_REFRESH_AQ ) vp9_cyclic_refresh_set_rate_and_dist_sb ( cpi -> cyclic_refresh , chosen_rate , chosen_dist ) ;
 encode_sb ( cpi , tile , tp , mi_row , mi_col , output_enabled , bsize , pc_tree ) ;
 }
 * rate = chosen_rate ;
 * dist = chosen_dist ;
 }
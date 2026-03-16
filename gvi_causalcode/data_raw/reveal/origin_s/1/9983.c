static void nonrd_pick_partition ( VP9_COMP * cpi , const TileInfo * const tile , TOKENEXTRA * * tp , int mi_row , int mi_col , BLOCK_SIZE bsize , int * rate , int64_t * dist , int do_recon , int64_t best_rd , PC_TREE * pc_tree ) {
 const SPEED_FEATURES * const sf = & cpi -> sf ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 const int ms = num_8x8_blocks_wide_lookup [ bsize ] / 2 ;
 TOKENEXTRA * tp_orig = * tp ;
 PICK_MODE_CONTEXT * ctx = & pc_tree -> none ;
 int i ;
 BLOCK_SIZE subsize = bsize ;
 int this_rate , sum_rate = 0 , best_rate = INT_MAX ;
 int64_t this_dist , sum_dist = 0 , best_dist = INT64_MAX ;
 int64_t sum_rd = 0 ;
 int do_split = bsize >= BLOCK_8X8 ;
 int do_rect = 1 ;
 const int force_horz_split = ( mi_row + ms >= cm -> mi_rows ) ;
 const int force_vert_split = ( mi_col + ms >= cm -> mi_cols ) ;
 const int xss = x -> e_mbd . plane [ 1 ] . subsampling_x ;
 const int yss = x -> e_mbd . plane [ 1 ] . subsampling_y ;
 int partition_none_allowed = ! force_horz_split && ! force_vert_split ;
 int partition_horz_allowed = ! force_vert_split && yss <= xss && bsize >= BLOCK_8X8 ;
 int partition_vert_allowed = ! force_horz_split && xss <= yss && bsize >= BLOCK_8X8 ;
 ( void ) * tp_orig ;
 assert ( num_8x8_blocks_wide_lookup [ bsize ] == num_8x8_blocks_high_lookup [ bsize ] ) ;
 if ( sf -> auto_min_max_partition_size ) {
 partition_none_allowed &= ( bsize <= sf -> max_partition_size && bsize >= sf -> min_partition_size ) ;
 partition_horz_allowed &= ( ( bsize <= sf -> max_partition_size && bsize > sf -> min_partition_size ) || force_horz_split ) ;
 partition_vert_allowed &= ( ( bsize <= sf -> max_partition_size && bsize > sf -> min_partition_size ) || force_vert_split ) ;
 do_split &= bsize > sf -> min_partition_size ;
 }
 if ( sf -> use_square_partition_only ) {
 partition_horz_allowed &= force_horz_split ;
 partition_vert_allowed &= force_vert_split ;
 }
 if ( partition_none_allowed ) {
 nonrd_pick_sb_modes ( cpi , tile , mi_row , mi_col , & this_rate , & this_dist , bsize , ctx ) ;
 ctx -> mic . mbmi = xd -> mi [ 0 ] -> mbmi ;
 ctx -> skip_txfm [ 0 ] = x -> skip_txfm [ 0 ] ;
 ctx -> skip = x -> skip ;
 if ( this_rate != INT_MAX ) {
 int pl = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 this_rate += cpi -> partition_cost [ pl ] [ PARTITION_NONE ] ;
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , this_rate , this_dist ) ;
 if ( sum_rd < best_rd ) {
 int64_t stop_thresh = 4096 ;
 int64_t stop_thresh_rd ;
 best_rate = this_rate ;
 best_dist = this_dist ;
 best_rd = sum_rd ;
 if ( bsize >= BLOCK_8X8 ) pc_tree -> partitioning = PARTITION_NONE ;
 stop_thresh >>= 8 - ( b_width_log2 ( bsize ) + b_height_log2 ( bsize ) ) ;
 stop_thresh_rd = RDCOST ( x -> rdmult , x -> rddiv , 0 , stop_thresh ) ;
 if ( ! x -> e_mbd . lossless && best_rd < stop_thresh_rd ) {
 do_split = 0 ;
 do_rect = 0 ;
 }
 }
 }
 }
 store_pred_mv ( x , ctx ) ;
 sum_rd = 0 ;
 if ( do_split ) {
 int pl = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 sum_rate += cpi -> partition_cost [ pl ] [ PARTITION_SPLIT ] ;
 subsize = get_subsize ( bsize , PARTITION_SPLIT ) ;
 for ( i = 0 ;
 i < 4 && sum_rd < best_rd ;
 ++ i ) {
 const int x_idx = ( i & 1 ) * ms ;
 const int y_idx = ( i >> 1 ) * ms ;
 if ( mi_row + y_idx >= cm -> mi_rows || mi_col + x_idx >= cm -> mi_cols ) continue ;
 load_pred_mv ( x , ctx ) ;
 nonrd_pick_partition ( cpi , tile , tp , mi_row + y_idx , mi_col + x_idx , subsize , & this_rate , & this_dist , 0 , best_rd - sum_rd , pc_tree -> split [ i ] ) ;
 if ( this_rate == INT_MAX ) {
 sum_rd = INT64_MAX ;
 }
 else {
 sum_rate += this_rate ;
 sum_dist += this_dist ;
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , sum_rate , sum_dist ) ;
 }
 }
 if ( sum_rd < best_rd ) {
 best_rate = sum_rate ;
 best_dist = sum_dist ;
 best_rd = sum_rd ;
 pc_tree -> partitioning = PARTITION_SPLIT ;
 }
 else {
 if ( sf -> less_rectangular_check ) do_rect &= ! partition_none_allowed ;
 }
 }
 if ( partition_horz_allowed && do_rect ) {
 subsize = get_subsize ( bsize , PARTITION_HORZ ) ;
 if ( sf -> adaptive_motion_search ) load_pred_mv ( x , ctx ) ;
 nonrd_pick_sb_modes ( cpi , tile , mi_row , mi_col , & this_rate , & this_dist , subsize , & pc_tree -> horizontal [ 0 ] ) ;
 pc_tree -> horizontal [ 0 ] . mic . mbmi = xd -> mi [ 0 ] -> mbmi ;
 pc_tree -> horizontal [ 0 ] . skip_txfm [ 0 ] = x -> skip_txfm [ 0 ] ;
 pc_tree -> horizontal [ 0 ] . skip = x -> skip ;
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , sum_rate , sum_dist ) ;
 if ( sum_rd < best_rd && mi_row + ms < cm -> mi_rows ) {
 load_pred_mv ( x , ctx ) ;
 nonrd_pick_sb_modes ( cpi , tile , mi_row + ms , mi_col , & this_rate , & this_dist , subsize , & pc_tree -> horizontal [ 1 ] ) ;
 pc_tree -> horizontal [ 1 ] . mic . mbmi = xd -> mi [ 0 ] -> mbmi ;
 pc_tree -> horizontal [ 1 ] . skip_txfm [ 0 ] = x -> skip_txfm [ 0 ] ;
 pc_tree -> horizontal [ 1 ] . skip = x -> skip ;
 if ( this_rate == INT_MAX ) {
 sum_rd = INT64_MAX ;
 }
 else {
 int pl = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 this_rate += cpi -> partition_cost [ pl ] [ PARTITION_HORZ ] ;
 sum_rate += this_rate ;
 sum_dist += this_dist ;
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , sum_rate , sum_dist ) ;
 }
 }
 if ( sum_rd < best_rd ) {
 best_rd = sum_rd ;
 best_rate = sum_rate ;
 best_dist = sum_dist ;
 pc_tree -> partitioning = PARTITION_HORZ ;
 }
 }
 if ( partition_vert_allowed && do_rect ) {
 subsize = get_subsize ( bsize , PARTITION_VERT ) ;
 if ( sf -> adaptive_motion_search ) load_pred_mv ( x , ctx ) ;
 nonrd_pick_sb_modes ( cpi , tile , mi_row , mi_col , & this_rate , & this_dist , subsize , & pc_tree -> vertical [ 0 ] ) ;
 pc_tree -> vertical [ 0 ] . mic . mbmi = xd -> mi [ 0 ] -> mbmi ;
 pc_tree -> vertical [ 0 ] . skip_txfm [ 0 ] = x -> skip_txfm [ 0 ] ;
 pc_tree -> vertical [ 0 ] . skip = x -> skip ;
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , sum_rate , sum_dist ) ;
 if ( sum_rd < best_rd && mi_col + ms < cm -> mi_cols ) {
 load_pred_mv ( x , ctx ) ;
 nonrd_pick_sb_modes ( cpi , tile , mi_row , mi_col + ms , & this_rate , & this_dist , subsize , & pc_tree -> vertical [ 1 ] ) ;
 pc_tree -> vertical [ 1 ] . mic . mbmi = xd -> mi [ 0 ] -> mbmi ;
 pc_tree -> vertical [ 1 ] . skip_txfm [ 0 ] = x -> skip_txfm [ 0 ] ;
 pc_tree -> vertical [ 1 ] . skip = x -> skip ;
 if ( this_rate == INT_MAX ) {
 sum_rd = INT64_MAX ;
 }
 else {
 int pl = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 this_rate += cpi -> partition_cost [ pl ] [ PARTITION_VERT ] ;
 sum_rate += this_rate ;
 sum_dist += this_dist ;
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , sum_rate , sum_dist ) ;
 }
 }
 if ( sum_rd < best_rd ) {
 best_rate = sum_rate ;
 best_dist = sum_dist ;
 best_rd = sum_rd ;
 pc_tree -> partitioning = PARTITION_VERT ;
 }
 }
 ( void ) best_rd ;
 * rate = best_rate ;
 * dist = best_dist ;
 if ( best_rate == INT_MAX ) return ;
 subsize = get_subsize ( bsize , pc_tree -> partitioning ) ;
 fill_mode_info_sb ( cm , x , mi_row , mi_col , bsize , subsize , pc_tree ) ;
 if ( best_rate < INT_MAX && best_dist < INT64_MAX && do_recon ) {
 int output_enabled = ( bsize == BLOCK_64X64 ) ;
 if ( ( oxcf -> aq_mode == COMPLEXITY_AQ ) && cm -> seg . update_map ) {
 vp9_select_in_frame_q_segment ( cpi , mi_row , mi_col , output_enabled , best_rate ) ;
 }
 if ( oxcf -> aq_mode == CYCLIC_REFRESH_AQ ) vp9_cyclic_refresh_set_rate_and_dist_sb ( cpi -> cyclic_refresh , best_rate , best_dist ) ;
 encode_sb_rt ( cpi , tile , tp , mi_row , mi_col , output_enabled , bsize , pc_tree ) ;
 }
 if ( bsize == BLOCK_64X64 ) {
 assert ( tp_orig < * tp ) ;
 assert ( best_rate < INT_MAX ) ;
 assert ( best_dist < INT64_MAX ) ;
 }
 else {
 assert ( tp_orig == * tp ) ;
 }
 }
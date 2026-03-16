static void rd_pick_partition ( VP9_COMP * cpi , const TileInfo * const tile , TOKENEXTRA * * tp , int mi_row , int mi_col , BLOCK_SIZE bsize , int * rate , int64_t * dist , int64_t best_rd , PC_TREE * pc_tree ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 const int mi_step = num_8x8_blocks_wide_lookup [ bsize ] / 2 ;
 ENTROPY_CONTEXT l [ 16 * MAX_MB_PLANE ] , a [ 16 * MAX_MB_PLANE ] ;
 PARTITION_CONTEXT sl [ 8 ] , sa [ 8 ] ;
 TOKENEXTRA * tp_orig = * tp ;
 PICK_MODE_CONTEXT * ctx = & pc_tree -> none ;
 int i , pl ;
 BLOCK_SIZE subsize ;
 int this_rate , sum_rate = 0 , best_rate = INT_MAX ;
 int64_t this_dist , sum_dist = 0 , best_dist = INT64_MAX ;
 int64_t sum_rd = 0 ;
 int do_split = bsize >= BLOCK_8X8 ;
 int do_rect = 1 ;
 const int force_horz_split = ( mi_row + mi_step >= cm -> mi_rows ) ;
 const int force_vert_split = ( mi_col + mi_step >= cm -> mi_cols ) ;
 const int xss = x -> e_mbd . plane [ 1 ] . subsampling_x ;
 const int yss = x -> e_mbd . plane [ 1 ] . subsampling_y ;
 BLOCK_SIZE min_size = cpi -> sf . min_partition_size ;
 BLOCK_SIZE max_size = cpi -> sf . max_partition_size ;

 int none_complexity = 0 ;

 int partition_horz_allowed = ! force_vert_split && yss <= xss && bsize >= BLOCK_8X8 ;
 int partition_vert_allowed = ! force_horz_split && xss <= yss && bsize >= BLOCK_8X8 ;
 ( void ) * tp_orig ;
 assert ( num_8x8_blocks_wide_lookup [ bsize ] == num_8x8_blocks_high_lookup [ bsize ] ) ;
 set_offsets ( cpi , tile , mi_row , mi_col , bsize ) ;
 if ( bsize == BLOCK_16X16 && cpi -> oxcf . aq_mode ) x -> mb_energy = vp9_block_energy ( cpi , x , bsize ) ;
 if ( cpi -> sf . cb_partition_search && bsize == BLOCK_16X16 ) {
 int cb_partition_search_ctrl = ( ( pc_tree -> index == 0 || pc_tree -> index == 3 ) + get_chessboard_index ( cm -> current_video_frame ) ) & 0x1 ;
 if ( cb_partition_search_ctrl && bsize > min_size && bsize < max_size ) set_partition_range ( cm , xd , mi_row , mi_col , bsize , & min_size , & max_size ) ;
 }
 if ( cpi -> sf . auto_min_max_partition_size ) {
 partition_none_allowed &= ( bsize <= max_size && bsize >= min_size ) ;
 partition_horz_allowed &= ( ( bsize <= max_size && bsize > min_size ) || force_horz_split ) ;
 partition_vert_allowed &= ( ( bsize <= max_size && bsize > min_size ) || force_vert_split ) ;
 do_split &= bsize > min_size ;
 }
 if ( cpi -> sf . use_square_partition_only ) {
 partition_horz_allowed &= force_horz_split ;
 partition_vert_allowed &= force_vert_split ;
 }
 save_context ( cpi , mi_row , mi_col , a , l , sa , sl , bsize ) ;

 set_offsets ( cpi , tile , mi_row , mi_col , bsize ) ;
 src_diff_var = get_sby_perpixel_diff_variance ( cpi , & cpi -> mb . plane [ 0 ] . src , mi_row , mi_col , bsize ) ;
 }

 int mb_row = mi_row >> 1 ;
 int mb_col = mi_col >> 1 ;
 int mb_row_end = MIN ( mb_row + num_16x16_blocks_high_lookup [ bsize ] , cm -> mb_rows ) ;
 int mb_col_end = MIN ( mb_col + num_16x16_blocks_wide_lookup [ bsize ] , cm -> mb_cols ) ;
 int r , c ;
 for ( r = mb_row ;
 r < mb_row_end ;
 r ++ ) {
 for ( c = mb_col ;
 c < mb_col_end ;
 c ++ ) {
 const int mb_index = r * cm -> mb_cols + c ;
 MOTION_DIRECTION this_mv ;
 MOTION_DIRECTION right_mv ;
 MOTION_DIRECTION bottom_mv ;
 this_mv = get_motion_direction_fp ( cpi -> twopass . this_frame_mb_stats [ mb_index ] ) ;
 if ( c != mb_col_end - 1 ) {
 right_mv = get_motion_direction_fp ( cpi -> twopass . this_frame_mb_stats [ mb_index + 1 ] ) ;
 none_complexity += get_motion_inconsistency ( this_mv , right_mv ) ;
 }
 if ( r != mb_row_end - 1 ) {
 bottom_mv = get_motion_direction_fp ( cpi -> twopass . this_frame_mb_stats [ mb_index + cm -> mb_cols ] ) ;
 none_complexity += get_motion_inconsistency ( this_mv , bottom_mv ) ;
 }
 }
 }
 if ( none_complexity > complexity_16x16_blocks_threshold [ bsize ] ) {
 partition_none_allowed = 0 ;
 }
 }

 rd_pick_sb_modes ( cpi , tile , mi_row , mi_col , & this_rate , & this_dist , bsize , ctx , best_rd , 0 ) ;
 if ( this_rate != INT_MAX ) {
 if ( bsize >= BLOCK_8X8 ) {
 pl = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 this_rate += cpi -> partition_cost [ pl ] [ PARTITION_NONE ] ;
 }
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , this_rate , this_dist ) ;
 if ( sum_rd < best_rd ) {
 int64_t dist_breakout_thr = cpi -> sf . partition_search_breakout_dist_thr ;
 int rate_breakout_thr = cpi -> sf . partition_search_breakout_rate_thr ;
 best_rate = this_rate ;
 best_dist = this_dist ;
 best_rd = sum_rd ;
 if ( bsize >= BLOCK_8X8 ) pc_tree -> partitioning = PARTITION_NONE ;
 dist_breakout_thr >>= 8 - ( b_width_log2 ( bsize ) + b_height_log2 ( bsize ) ) ;
 if ( ! x -> e_mbd . lossless && ( ctx -> skippable && best_dist < dist_breakout_thr && best_rate < rate_breakout_thr ) ) {
 do_split = 0 ;
 do_rect = 0 ;
 }

 int mb_row = mi_row >> 1 ;
 int mb_col = mi_col >> 1 ;
 int mb_row_end = MIN ( mb_row + num_16x16_blocks_high_lookup [ bsize ] , cm -> mb_rows ) ;
 int mb_col_end = MIN ( mb_col + num_16x16_blocks_wide_lookup [ bsize ] , cm -> mb_cols ) ;
 int r , c ;
 int skip = 1 ;
 for ( r = mb_row ;
 r < mb_row_end ;
 r ++ ) {
 for ( c = mb_col ;
 c < mb_col_end ;
 c ++ ) {
 const int mb_index = r * cm -> mb_cols + c ;
 if ( ! ( cpi -> twopass . this_frame_mb_stats [ mb_index ] & FPMB_MOTION_ZERO_MASK ) || ! ( cpi -> twopass . this_frame_mb_stats [ mb_index ] & FPMB_ERROR_SMALL_MASK ) ) {
 skip = 0 ;
 break ;
 }
 }
 if ( skip == 0 ) {
 break ;
 }
 }
 if ( skip ) {
 if ( src_diff_var == UINT_MAX ) {
 set_offsets ( cpi , tile , mi_row , mi_col , bsize ) ;
 src_diff_var = get_sby_perpixel_diff_variance ( cpi , & cpi -> mb . plane [ 0 ] . src , mi_row , mi_col , bsize ) ;
 }
 if ( src_diff_var < 8 ) {
 do_split = 0 ;
 do_rect = 0 ;
 }
 }
 }

 }
 restore_context ( cpi , mi_row , mi_col , a , l , sa , sl , bsize ) ;
 }
 if ( cpi -> sf . adaptive_motion_search ) store_pred_mv ( x , ctx ) ;
 sum_rd = 0 ;
 if ( do_split ) {
 subsize = get_subsize ( bsize , PARTITION_SPLIT ) ;
 if ( bsize == BLOCK_8X8 ) {
 i = 4 ;
 if ( cpi -> sf . adaptive_pred_interp_filter && partition_none_allowed ) pc_tree -> leaf_split [ 0 ] -> pred_interp_filter = ctx -> mic . mbmi . interp_filter ;
 rd_pick_sb_modes ( cpi , tile , mi_row , mi_col , & sum_rate , & sum_dist , subsize , pc_tree -> leaf_split [ 0 ] , best_rd , 0 ) ;
 if ( sum_rate == INT_MAX ) sum_rd = INT64_MAX ;
 else sum_rd = RDCOST ( x -> rdmult , x -> rddiv , sum_rate , sum_dist ) ;
 }
 else {
 for ( i = 0 ;
 i < 4 && sum_rd < best_rd ;
 ++ i ) {
 const int x_idx = ( i & 1 ) * mi_step ;
 const int y_idx = ( i >> 1 ) * mi_step ;
 if ( mi_row + y_idx >= cm -> mi_rows || mi_col + x_idx >= cm -> mi_cols ) continue ;
 if ( cpi -> sf . adaptive_motion_search ) load_pred_mv ( x , ctx ) ;
 pc_tree -> split [ i ] -> index = i ;
 rd_pick_partition ( cpi , tile , tp , mi_row + y_idx , mi_col + x_idx , subsize , & this_rate , & this_dist , best_rd - sum_rd , pc_tree -> split [ i ] ) ;
 if ( this_rate == INT_MAX ) {
 sum_rd = INT64_MAX ;
 }
 else {
 sum_rate += this_rate ;
 sum_dist += this_dist ;
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , sum_rate , sum_dist ) ;
 }
 }
 }
 if ( sum_rd < best_rd && i == 4 ) {
 pl = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 sum_rate += cpi -> partition_cost [ pl ] [ PARTITION_SPLIT ] ;
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , sum_rate , sum_dist ) ;
 if ( sum_rd < best_rd ) {
 best_rate = sum_rate ;
 best_dist = sum_dist ;
 best_rd = sum_rd ;
 pc_tree -> partitioning = PARTITION_SPLIT ;
 }
 }
 else {
 if ( cpi -> sf . less_rectangular_check ) do_rect &= ! partition_none_allowed ;
 }
 restore_context ( cpi , mi_row , mi_col , a , l , sa , sl , bsize ) ;
 }
 if ( partition_horz_allowed && do_rect ) {
 subsize = get_subsize ( bsize , PARTITION_HORZ ) ;
 if ( cpi -> sf . adaptive_motion_search ) load_pred_mv ( x , ctx ) ;
 if ( cpi -> sf . adaptive_pred_interp_filter && bsize == BLOCK_8X8 && partition_none_allowed ) pc_tree -> horizontal [ 0 ] . pred_interp_filter = ctx -> mic . mbmi . interp_filter ;
 rd_pick_sb_modes ( cpi , tile , mi_row , mi_col , & sum_rate , & sum_dist , subsize , & pc_tree -> horizontal [ 0 ] , best_rd , 0 ) ;
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , sum_rate , sum_dist ) ;
 if ( sum_rd < best_rd && mi_row + mi_step < cm -> mi_rows ) {
 PICK_MODE_CONTEXT * ctx = & pc_tree -> horizontal [ 0 ] ;
 update_state ( cpi , ctx , mi_row , mi_col , subsize , 0 ) ;
 encode_superblock ( cpi , tp , 0 , mi_row , mi_col , subsize , ctx ) ;
 if ( cpi -> sf . adaptive_motion_search ) load_pred_mv ( x , ctx ) ;
 if ( cpi -> sf . adaptive_pred_interp_filter && bsize == BLOCK_8X8 && partition_none_allowed ) pc_tree -> horizontal [ 1 ] . pred_interp_filter = ctx -> mic . mbmi . interp_filter ;
 rd_pick_sb_modes ( cpi , tile , mi_row + mi_step , mi_col , & this_rate , & this_dist , subsize , & pc_tree -> horizontal [ 1 ] , best_rd - sum_rd , 1 ) ;
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
 pl = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 sum_rate += cpi -> partition_cost [ pl ] [ PARTITION_HORZ ] ;
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , sum_rate , sum_dist ) ;
 if ( sum_rd < best_rd ) {
 best_rd = sum_rd ;
 best_rate = sum_rate ;
 best_dist = sum_dist ;
 pc_tree -> partitioning = PARTITION_HORZ ;
 }
 }
 restore_context ( cpi , mi_row , mi_col , a , l , sa , sl , bsize ) ;
 }
 if ( partition_vert_allowed && do_rect ) {
 subsize = get_subsize ( bsize , PARTITION_VERT ) ;
 if ( cpi -> sf . adaptive_motion_search ) load_pred_mv ( x , ctx ) ;
 if ( cpi -> sf . adaptive_pred_interp_filter && bsize == BLOCK_8X8 && partition_none_allowed ) pc_tree -> vertical [ 0 ] . pred_interp_filter = ctx -> mic . mbmi . interp_filter ;
 rd_pick_sb_modes ( cpi , tile , mi_row , mi_col , & sum_rate , & sum_dist , subsize , & pc_tree -> vertical [ 0 ] , best_rd , 0 ) ;
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , sum_rate , sum_dist ) ;
 if ( sum_rd < best_rd && mi_col + mi_step < cm -> mi_cols ) {
 update_state ( cpi , & pc_tree -> vertical [ 0 ] , mi_row , mi_col , subsize , 0 ) ;
 encode_superblock ( cpi , tp , 0 , mi_row , mi_col , subsize , & pc_tree -> vertical [ 0 ] ) ;
 if ( cpi -> sf . adaptive_motion_search ) load_pred_mv ( x , ctx ) ;
 if ( cpi -> sf . adaptive_pred_interp_filter && bsize == BLOCK_8X8 && partition_none_allowed ) pc_tree -> vertical [ 1 ] . pred_interp_filter = ctx -> mic . mbmi . interp_filter ;
 rd_pick_sb_modes ( cpi , tile , mi_row , mi_col + mi_step , & this_rate , & this_dist , subsize , & pc_tree -> vertical [ 1 ] , best_rd - sum_rd , 1 ) ;
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
 pl = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 sum_rate += cpi -> partition_cost [ pl ] [ PARTITION_VERT ] ;
 sum_rd = RDCOST ( x -> rdmult , x -> rddiv , sum_rate , sum_dist ) ;
 if ( sum_rd < best_rd ) {
 best_rate = sum_rate ;
 best_dist = sum_dist ;
 best_rd = sum_rd ;
 pc_tree -> partitioning = PARTITION_VERT ;
 }
 }
 restore_context ( cpi , mi_row , mi_col , a , l , sa , sl , bsize ) ;
 }
 ( void ) best_rd ;
 * rate = best_rate ;
 * dist = best_dist ;
 if ( best_rate < INT_MAX && best_dist < INT64_MAX && pc_tree -> index != 3 ) {
 int output_enabled = ( bsize == BLOCK_64X64 ) ;
 if ( ( cpi -> oxcf . aq_mode == COMPLEXITY_AQ ) && cm -> seg . update_map ) vp9_select_in_frame_q_segment ( cpi , mi_row , mi_col , output_enabled , best_rate ) ;
 if ( cpi -> oxcf . aq_mode == CYCLIC_REFRESH_AQ ) vp9_cyclic_refresh_set_rate_and_dist_sb ( cpi -> cyclic_refresh , best_rate , best_dist ) ;
 encode_sb ( cpi , tile , tp , mi_row , mi_col , output_enabled , bsize , pc_tree ) ;
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
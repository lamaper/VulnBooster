static int64_t rd_pick_intra_sub_8x8_y_mode ( VP9_COMP * cpi , MACROBLOCK * mb , int * rate , int * rate_y , int64_t * distortion , int64_t best_rd ) {
 int i , j ;
 const MACROBLOCKD * const xd = & mb -> e_mbd ;
 MODE_INFO * const mic = xd -> mi [ 0 ] ;
 const MODE_INFO * above_mi = xd -> mi [ - xd -> mi_stride ] ;
 const MODE_INFO * left_mi = xd -> left_available ? xd -> mi [ - 1 ] : NULL ;
 const BLOCK_SIZE bsize = xd -> mi [ 0 ] -> mbmi . sb_type ;
 const int num_4x4_blocks_wide = num_4x4_blocks_wide_lookup [ bsize ] ;
 const int num_4x4_blocks_high = num_4x4_blocks_high_lookup [ bsize ] ;
 int idx , idy ;
 int cost = 0 ;
 int64_t total_distortion = 0 ;
 int tot_rate_y = 0 ;
 int64_t total_rd = 0 ;
 ENTROPY_CONTEXT t_above [ 4 ] , t_left [ 4 ] ;
 const int * bmode_costs = cpi -> mbmode_cost ;
 vpx_memcpy ( t_above , xd -> plane [ 0 ] . above_context , sizeof ( t_above ) ) ;
 vpx_memcpy ( t_left , xd -> plane [ 0 ] . left_context , sizeof ( t_left ) ) ;
 for ( idy = 0 ;
 idy < 2 ;
 idy += num_4x4_blocks_high ) {
 for ( idx = 0 ;
 idx < 2 ;
 idx += num_4x4_blocks_wide ) {
 PREDICTION_MODE best_mode = DC_PRED ;
 int r = INT_MAX , ry = INT_MAX ;
 int64_t d = INT64_MAX , this_rd = INT64_MAX ;
 i = idy * 2 + idx ;
 if ( cpi -> common . frame_type == KEY_FRAME ) {
 const PREDICTION_MODE A = vp9_above_block_mode ( mic , above_mi , i ) ;
 const PREDICTION_MODE L = vp9_left_block_mode ( mic , left_mi , i ) ;
 bmode_costs = cpi -> y_mode_costs [ A ] [ L ] ;
 }
 this_rd = rd_pick_intra4x4block ( cpi , mb , i , & best_mode , bmode_costs , t_above + idx , t_left + idy , & r , & ry , & d , bsize , best_rd - total_rd ) ;
 if ( this_rd >= best_rd - total_rd ) return INT64_MAX ;
 total_rd += this_rd ;
 cost += r ;
 total_distortion += d ;
 tot_rate_y += ry ;
 mic -> bmi [ i ] . as_mode = best_mode ;
 for ( j = 1 ;
 j < num_4x4_blocks_high ;
 ++ j ) mic -> bmi [ i + j * 2 ] . as_mode = best_mode ;
 for ( j = 1 ;
 j < num_4x4_blocks_wide ;
 ++ j ) mic -> bmi [ i + j ] . as_mode = best_mode ;
 if ( total_rd >= best_rd ) return INT64_MAX ;
 }
 }
 * rate = cost ;
 * rate_y = tot_rate_y ;
 * distortion = total_distortion ;
 mic -> mbmi . mode = mic -> bmi [ 3 ] . as_mode ;
 return RDCOST ( mb -> rdmult , mb -> rddiv , cost , total_distortion ) ;
 }
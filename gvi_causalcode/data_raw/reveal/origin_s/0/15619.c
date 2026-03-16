static int64_t rd_pick_intra_sby_mode ( VP9_COMP * cpi , MACROBLOCK * x , int * rate , int * rate_tokenonly , int64_t * distortion , int * skippable , BLOCK_SIZE bsize , int64_t tx_cache [ TX_MODES ] , int64_t best_rd ) {
 PREDICTION_MODE mode ;
 PREDICTION_MODE mode_selected = DC_PRED ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 MODE_INFO * const mic = xd -> mi [ 0 ] . src_mi ;
 int this_rate , this_rate_tokenonly , s ;
 int64_t this_distortion , this_rd ;
 TX_SIZE best_tx = TX_4X4 ;
 int i ;
 int * bmode_costs = cpi -> mbmode_cost ;
 if ( cpi -> sf . tx_size_search_method == USE_FULL_RD ) for ( i = 0 ;
 i < TX_MODES ;
 i ++ ) tx_cache [ i ] = INT64_MAX ;
 for ( mode = DC_PRED ;
 mode <= TM_PRED ;
 mode ++ ) {
 int64_t local_tx_cache [ TX_MODES ] ;
 MODE_INFO * above_mi = xd -> mi [ - xd -> mi_stride ] . src_mi ;
 MODE_INFO * left_mi = xd -> left_available ? xd -> mi [ - 1 ] . src_mi : NULL ;
 if ( cpi -> common . frame_type == KEY_FRAME ) {
 const PREDICTION_MODE A = vp9_above_block_mode ( mic , above_mi , 0 ) ;
 const PREDICTION_MODE L = vp9_left_block_mode ( mic , left_mi , 0 ) ;
 bmode_costs = cpi -> y_mode_costs [ A ] [ L ] ;
 }
 mic -> mbmi . mode = mode ;
 super_block_yrd ( cpi , x , & this_rate_tokenonly , & this_distortion , & s , NULL , bsize , local_tx_cache , best_rd ) ;
 if ( this_rate_tokenonly == INT_MAX ) continue ;
 this_rate = this_rate_tokenonly + bmode_costs [ mode ] ;
 this_rd = RDCOST ( x -> rdmult , x -> rddiv , this_rate , this_distortion ) ;
 if ( this_rd < best_rd ) {
 mode_selected = mode ;
 best_rd = this_rd ;
 best_tx = mic -> mbmi . tx_size ;
 * rate = this_rate ;
 * rate_tokenonly = this_rate_tokenonly ;
 * distortion = this_distortion ;
 * skippable = s ;
 }
 if ( cpi -> sf . tx_size_search_method == USE_FULL_RD && this_rd < INT64_MAX ) {
 for ( i = 0 ;
 i < TX_MODES && local_tx_cache [ i ] < INT64_MAX ;
 i ++ ) {
 const int64_t adj_rd = this_rd + local_tx_cache [ i ] - local_tx_cache [ cpi -> common . tx_mode ] ;
 if ( adj_rd < tx_cache [ i ] ) {
 tx_cache [ i ] = adj_rd ;
 }
 }
 }
 }
 mic -> mbmi . mode = mode_selected ;
 mic -> mbmi . tx_size = best_tx ;
 return best_rd ;
 }
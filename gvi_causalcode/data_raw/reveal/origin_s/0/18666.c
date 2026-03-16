static int64_t rd_pick_intra_sbuv_mode ( VP9_COMP * cpi , MACROBLOCK * x , PICK_MODE_CONTEXT * ctx , int * rate , int * rate_tokenonly , int64_t * distortion , int * skippable , BLOCK_SIZE bsize , TX_SIZE max_tx_size ) {
 MACROBLOCKD * xd = & x -> e_mbd ;
 PREDICTION_MODE mode ;
 PREDICTION_MODE mode_selected = DC_PRED ;
 int64_t best_rd = INT64_MAX , this_rd ;
 int this_rate_tokenonly , this_rate , s ;
 int64_t this_distortion , this_sse ;
 for ( mode = DC_PRED ;
 mode <= TM_PRED ;
 ++ mode ) {
 if ( ! ( cpi -> sf . intra_uv_mode_mask [ max_tx_size ] & ( 1 << mode ) ) ) continue ;
 xd -> mi [ 0 ] . src_mi -> mbmi . uv_mode = mode ;
 super_block_uvrd ( cpi , x , & this_rate_tokenonly , & this_distortion , & s , & this_sse , bsize , best_rd ) ;
 if ( this_rate_tokenonly == INT_MAX ) continue ;
 this_rate = this_rate_tokenonly + cpi -> intra_uv_mode_cost [ cpi -> common . frame_type ] [ mode ] ;
 this_rd = RDCOST ( x -> rdmult , x -> rddiv , this_rate , this_distortion ) ;
 if ( this_rd < best_rd ) {
 mode_selected = mode ;
 best_rd = this_rd ;
 * rate = this_rate ;
 * rate_tokenonly = this_rate_tokenonly ;
 * distortion = this_distortion ;
 * skippable = s ;
 if ( ! x -> select_tx_size ) swap_block_ptr ( x , ctx , 2 , 0 , 1 , MAX_MB_PLANE ) ;
 }
 }
 xd -> mi [ 0 ] . src_mi -> mbmi . uv_mode = mode_selected ;
 return best_rd ;
 }
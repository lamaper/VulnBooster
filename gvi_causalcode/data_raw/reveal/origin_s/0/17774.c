void vp9_rd_pick_intra_mode_sb ( VP9_COMP * cpi , MACROBLOCK * x , int * returnrate , int64_t * returndist , BLOCK_SIZE bsize , PICK_MODE_CONTEXT * ctx , int64_t best_rd ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 struct macroblockd_plane * const pd = xd -> plane ;
 int rate_y = 0 , rate_uv = 0 , rate_y_tokenonly = 0 , rate_uv_tokenonly = 0 ;
 int y_skip = 0 , uv_skip = 0 ;
 int64_t dist_y = 0 , dist_uv = 0 , tx_cache [ TX_MODES ] = {
 0 }
 ;
 TX_SIZE max_uv_tx_size ;
 x -> skip_encode = 0 ;
 ctx -> skip = 0 ;
 xd -> mi [ 0 ] . src_mi -> mbmi . ref_frame [ 0 ] = INTRA_FRAME ;
 if ( bsize >= BLOCK_8X8 ) {
 if ( rd_pick_intra_sby_mode ( cpi , x , & rate_y , & rate_y_tokenonly , & dist_y , & y_skip , bsize , tx_cache , best_rd ) >= best_rd ) {
 * returnrate = INT_MAX ;
 return ;
 }
 max_uv_tx_size = get_uv_tx_size_impl ( xd -> mi [ 0 ] . src_mi -> mbmi . tx_size , bsize , pd [ 1 ] . subsampling_x , pd [ 1 ] . subsampling_y ) ;
 rd_pick_intra_sbuv_mode ( cpi , x , ctx , & rate_uv , & rate_uv_tokenonly , & dist_uv , & uv_skip , bsize , max_uv_tx_size ) ;
 }
 else {
 y_skip = 0 ;
 if ( rd_pick_intra_sub_8x8_y_mode ( cpi , x , & rate_y , & rate_y_tokenonly , & dist_y , best_rd ) >= best_rd ) {
 * returnrate = INT_MAX ;
 return ;
 }
 max_uv_tx_size = get_uv_tx_size_impl ( xd -> mi [ 0 ] . src_mi -> mbmi . tx_size , bsize , pd [ 1 ] . subsampling_x , pd [ 1 ] . subsampling_y ) ;
 rd_pick_intra_sbuv_mode ( cpi , x , ctx , & rate_uv , & rate_uv_tokenonly , & dist_uv , & uv_skip , BLOCK_8X8 , max_uv_tx_size ) ;
 }
 if ( y_skip && uv_skip ) {
 * returnrate = rate_y + rate_uv - rate_y_tokenonly - rate_uv_tokenonly + vp9_cost_bit ( vp9_get_skip_prob ( cm , xd ) , 1 ) ;
 * returndist = dist_y + dist_uv ;
 vp9_zero ( ctx -> tx_rd_diff ) ;
 }
 else {
 int i ;
 * returnrate = rate_y + rate_uv + vp9_cost_bit ( vp9_get_skip_prob ( cm , xd ) , 0 ) ;
 * returndist = dist_y + dist_uv ;
 if ( cpi -> sf . tx_size_search_method == USE_FULL_RD ) for ( i = 0 ;
 i < TX_MODES ;
 i ++ ) {
 if ( tx_cache [ i ] < INT64_MAX && tx_cache [ cm -> tx_mode ] < INT64_MAX ) ctx -> tx_rd_diff [ i ] = tx_cache [ i ] - tx_cache [ cm -> tx_mode ] ;
 else ctx -> tx_rd_diff [ i ] = 0 ;
 }
 }
 ctx -> mic = * xd -> mi [ 0 ] . src_mi ;
 }
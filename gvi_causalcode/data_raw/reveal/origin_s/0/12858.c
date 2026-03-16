static int64_t handle_inter_mode ( VP9_COMP * cpi , MACROBLOCK * x , BLOCK_SIZE bsize , int64_t txfm_cache [ ] , int * rate2 , int64_t * distortion , int * skippable , int * rate_y , int64_t * distortion_y , int * rate_uv , int64_t * distortion_uv , int * disable_skip , int_mv ( * mode_mv ) [ MAX_REF_FRAMES ] , int mi_row , int mi_col , int_mv single_newmv [ MAX_REF_FRAMES ] , INTERP_FILTER ( * single_filter ) [ MAX_REF_FRAMES ] , int ( * single_skippable ) [ MAX_REF_FRAMES ] , int64_t * psse , const int64_t ref_best_rd ) {
 VP9_COMMON * cm = & cpi -> common ;
 RD_OPT * rd_opt = & cpi -> rd ;
 MACROBLOCKD * xd = & x -> e_mbd ;
 MB_MODE_INFO * mbmi = & xd -> mi [ 0 ] . src_mi -> mbmi ;
 const int is_comp_pred = has_second_ref ( mbmi ) ;
 const int this_mode = mbmi -> mode ;
 int_mv * frame_mv = mode_mv [ this_mode ] ;
 int i ;
 int refs [ 2 ] = {
 mbmi -> ref_frame [ 0 ] , ( mbmi -> ref_frame [ 1 ] < 0 ? 0 : mbmi -> ref_frame [ 1 ] ) }
 ;
 int_mv cur_mv [ 2 ] ;
 int64_t this_rd = 0 ;
 DECLARE_ALIGNED_ARRAY ( 16 , uint8_t , tmp_buf , MAX_MB_PLANE * 64 * 64 ) ;
 int pred_exists = 0 ;
 int intpel_mv ;
 int64_t rd , tmp_rd , best_rd = INT64_MAX ;
 int best_needs_copy = 0 ;
 uint8_t * orig_dst [ MAX_MB_PLANE ] ;
 int orig_dst_stride [ MAX_MB_PLANE ] ;
 int rs = 0 ;
 INTERP_FILTER best_filter = SWITCHABLE ;
 uint8_t skip_txfm [ MAX_MB_PLANE << 2 ] = {
 0 }
 ;
 int64_t bsse [ MAX_MB_PLANE << 2 ] = {
 0 }
 ;
 int bsl = mi_width_log2_lookup [ bsize ] ;
 int pred_filter_search = cpi -> sf . cb_pred_filter_search ? ( ( ( mi_row + mi_col ) >> bsl ) + get_chessboard_index ( cm -> current_video_frame ) ) & 0x1 : 0 ;
 if ( pred_filter_search ) {
 INTERP_FILTER af = SWITCHABLE , lf = SWITCHABLE ;
 if ( xd -> up_available ) af = xd -> mi [ - xd -> mi_stride ] . src_mi -> mbmi . interp_filter ;
 if ( xd -> left_available ) lf = xd -> mi [ - 1 ] . src_mi -> mbmi . interp_filter ;
 if ( ( this_mode != NEWMV ) || ( af == lf ) ) best_filter = af ;
 }
 if ( is_comp_pred ) {
 if ( frame_mv [ refs [ 0 ] ] . as_int == INVALID_MV || frame_mv [ refs [ 1 ] ] . as_int == INVALID_MV ) return INT64_MAX ;
 if ( cpi -> sf . adaptive_mode_search ) {
 if ( single_filter [ this_mode ] [ refs [ 0 ] ] == single_filter [ this_mode ] [ refs [ 1 ] ] ) best_filter = single_filter [ this_mode ] [ refs [ 0 ] ] ;
 }
 }
 if ( this_mode == NEWMV ) {
 int rate_mv ;
 if ( is_comp_pred ) {
 frame_mv [ refs [ 0 ] ] . as_int = single_newmv [ refs [ 0 ] ] . as_int ;
 frame_mv [ refs [ 1 ] ] . as_int = single_newmv [ refs [ 1 ] ] . as_int ;
 if ( cpi -> sf . comp_inter_joint_search_thresh <= bsize ) {
 joint_motion_search ( cpi , x , bsize , frame_mv , mi_row , mi_col , single_newmv , & rate_mv ) ;
 }
 else {
 rate_mv = vp9_mv_bit_cost ( & frame_mv [ refs [ 0 ] ] . as_mv , & mbmi -> ref_mvs [ refs [ 0 ] ] [ 0 ] . as_mv , x -> nmvjointcost , x -> mvcost , MV_COST_WEIGHT ) ;
 rate_mv += vp9_mv_bit_cost ( & frame_mv [ refs [ 1 ] ] . as_mv , & mbmi -> ref_mvs [ refs [ 1 ] ] [ 0 ] . as_mv , x -> nmvjointcost , x -> mvcost , MV_COST_WEIGHT ) ;
 }
 * rate2 += rate_mv ;
 }
 else {
 int_mv tmp_mv ;
 single_motion_search ( cpi , x , bsize , mi_row , mi_col , & tmp_mv , & rate_mv ) ;
 if ( tmp_mv . as_int == INVALID_MV ) return INT64_MAX ;
 * rate2 += rate_mv ;
 frame_mv [ refs [ 0 ] ] . as_int = xd -> mi [ 0 ] . src_mi -> bmi [ 0 ] . as_mv [ 0 ] . as_int = tmp_mv . as_int ;
 single_newmv [ refs [ 0 ] ] . as_int = tmp_mv . as_int ;
 }
 }
 for ( i = 0 ;
 i < is_comp_pred + 1 ;
 ++ i ) {
 cur_mv [ i ] = frame_mv [ refs [ i ] ] ;
 if ( this_mode != NEWMV ) clamp_mv2 ( & cur_mv [ i ] . as_mv , xd ) ;
 if ( mv_check_bounds ( x , & cur_mv [ i ] . as_mv ) ) return INT64_MAX ;
 mbmi -> mv [ i ] . as_int = cur_mv [ i ] . as_int ;
 }
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 i ++ ) {
 orig_dst [ i ] = xd -> plane [ i ] . dst . buf ;
 orig_dst_stride [ i ] = xd -> plane [ i ] . dst . stride ;
 }
 * rate2 += cost_mv_ref ( cpi , this_mode , mbmi -> mode_context [ refs [ 0 ] ] ) ;
 if ( RDCOST ( x -> rdmult , x -> rddiv , * rate2 , 0 ) > ref_best_rd && mbmi -> mode != NEARESTMV ) return INT64_MAX ;
 pred_exists = 0 ;
 intpel_mv = ! mv_has_subpel ( & mbmi -> mv [ 0 ] . as_mv ) ;
 if ( is_comp_pred ) intpel_mv &= ! mv_has_subpel ( & mbmi -> mv [ 1 ] . as_mv ) ;
 rd_opt -> mask_filter = 0 ;
 for ( i = 0 ;
 i < SWITCHABLE_FILTER_CONTEXTS ;
 ++ i ) rd_opt -> filter_cache [ i ] = INT64_MAX ;
 if ( cm -> interp_filter != BILINEAR ) {
 if ( x -> source_variance < cpi -> sf . disable_filter_search_var_thresh ) {
 best_filter = EIGHTTAP ;
 }
 else if ( best_filter == SWITCHABLE ) {
 int newbest ;
 int tmp_rate_sum = 0 ;
 int64_t tmp_dist_sum = 0 ;
 for ( i = 0 ;
 i < SWITCHABLE_FILTERS ;
 ++ i ) {
 int j ;
 int64_t rs_rd ;
 mbmi -> interp_filter = i ;
 rs = vp9_get_switchable_rate ( cpi ) ;
 rs_rd = RDCOST ( x -> rdmult , x -> rddiv , rs , 0 ) ;
 if ( i > 0 && intpel_mv ) {
 rd = RDCOST ( x -> rdmult , x -> rddiv , tmp_rate_sum , tmp_dist_sum ) ;
 rd_opt -> filter_cache [ i ] = rd ;
 rd_opt -> filter_cache [ SWITCHABLE_FILTERS ] = MIN ( rd_opt -> filter_cache [ SWITCHABLE_FILTERS ] , rd + rs_rd ) ;
 if ( cm -> interp_filter == SWITCHABLE ) rd += rs_rd ;
 rd_opt -> mask_filter = MAX ( rd_opt -> mask_filter , rd ) ;
 }
 else {
 int rate_sum = 0 ;
 int64_t dist_sum = 0 ;
 if ( i > 0 && cpi -> sf . adaptive_interp_filter_search && ( cpi -> sf . interp_filter_search_mask & ( 1 << i ) ) ) {
 rate_sum = INT_MAX ;
 dist_sum = INT64_MAX ;
 continue ;
 }
 if ( ( cm -> interp_filter == SWITCHABLE && ( ! i || best_needs_copy ) ) || ( cm -> interp_filter != SWITCHABLE && ( cm -> interp_filter == mbmi -> interp_filter || ( i == 0 && intpel_mv ) ) ) ) {
 restore_dst_buf ( xd , orig_dst , orig_dst_stride ) ;
 }
 else {
 for ( j = 0 ;
 j < MAX_MB_PLANE ;
 j ++ ) {
 xd -> plane [ j ] . dst . buf = tmp_buf + j * 64 * 64 ;
 xd -> plane [ j ] . dst . stride = 64 ;
 }
 }
 vp9_build_inter_predictors_sb ( xd , mi_row , mi_col , bsize ) ;
 model_rd_for_sb ( cpi , bsize , x , xd , & rate_sum , & dist_sum ) ;
 rd = RDCOST ( x -> rdmult , x -> rddiv , rate_sum , dist_sum ) ;
 rd_opt -> filter_cache [ i ] = rd ;
 rd_opt -> filter_cache [ SWITCHABLE_FILTERS ] = MIN ( rd_opt -> filter_cache [ SWITCHABLE_FILTERS ] , rd + rs_rd ) ;
 if ( cm -> interp_filter == SWITCHABLE ) rd += rs_rd ;
 rd_opt -> mask_filter = MAX ( rd_opt -> mask_filter , rd ) ;
 if ( i == 0 && intpel_mv ) {
 tmp_rate_sum = rate_sum ;
 tmp_dist_sum = dist_sum ;
 }
 }
 if ( i == 0 && cpi -> sf . use_rd_breakout && ref_best_rd < INT64_MAX ) {
 if ( rd / 2 > ref_best_rd ) {
 restore_dst_buf ( xd , orig_dst , orig_dst_stride ) ;
 return INT64_MAX ;
 }
 }
 newbest = i == 0 || rd < best_rd ;
 if ( newbest ) {
 best_rd = rd ;
 best_filter = mbmi -> interp_filter ;
 if ( cm -> interp_filter == SWITCHABLE && i && ! intpel_mv ) best_needs_copy = ! best_needs_copy ;
 vpx_memcpy ( skip_txfm , x -> skip_txfm , sizeof ( skip_txfm ) ) ;
 vpx_memcpy ( bsse , x -> bsse , sizeof ( bsse ) ) ;
 }
 if ( ( cm -> interp_filter == SWITCHABLE && newbest ) || ( cm -> interp_filter != SWITCHABLE && cm -> interp_filter == mbmi -> interp_filter ) ) {
 pred_exists = 1 ;
 tmp_rd = best_rd ;
 }
 }
 restore_dst_buf ( xd , orig_dst , orig_dst_stride ) ;
 }
 }
 mbmi -> interp_filter = cm -> interp_filter != SWITCHABLE ? cm -> interp_filter : best_filter ;
 rs = cm -> interp_filter == SWITCHABLE ? vp9_get_switchable_rate ( cpi ) : 0 ;
 if ( pred_exists ) {
 if ( best_needs_copy ) {
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 i ++ ) {
 xd -> plane [ i ] . dst . buf = tmp_buf + i * 64 * 64 ;
 xd -> plane [ i ] . dst . stride = 64 ;
 }
 }
 rd = tmp_rd + RDCOST ( x -> rdmult , x -> rddiv , rs , 0 ) ;
 }
 else {
 int tmp_rate ;
 int64_t tmp_dist ;
 vp9_build_inter_predictors_sb ( xd , mi_row , mi_col , bsize ) ;
 model_rd_for_sb ( cpi , bsize , x , xd , & tmp_rate , & tmp_dist ) ;
 rd = RDCOST ( x -> rdmult , x -> rddiv , rs + tmp_rate , tmp_dist ) ;
 vpx_memcpy ( skip_txfm , x -> skip_txfm , sizeof ( skip_txfm ) ) ;
 vpx_memcpy ( bsse , x -> bsse , sizeof ( bsse ) ) ;
 }
 if ( ! is_comp_pred ) single_filter [ this_mode ] [ refs [ 0 ] ] = mbmi -> interp_filter ;
 if ( cpi -> sf . adaptive_mode_search ) if ( is_comp_pred ) if ( single_skippable [ this_mode ] [ refs [ 0 ] ] && single_skippable [ this_mode ] [ refs [ 1 ] ] ) vpx_memset ( skip_txfm , 1 , sizeof ( skip_txfm ) ) ;
 if ( cpi -> sf . use_rd_breakout && ref_best_rd < INT64_MAX ) {
 if ( rd / 2 > ref_best_rd ) {
 restore_dst_buf ( xd , orig_dst , orig_dst_stride ) ;
 return INT64_MAX ;
 }
 }
 if ( cm -> interp_filter == SWITCHABLE ) * rate2 += rs ;
 if ( ! is_comp_pred ) {
 if ( cpi -> allow_encode_breakout ) rd_encode_breakout_test ( cpi , x , bsize , rate2 , distortion , distortion_uv , disable_skip ) ;
 }
 vpx_memcpy ( x -> skip_txfm , skip_txfm , sizeof ( skip_txfm ) ) ;
 vpx_memcpy ( x -> bsse , bsse , sizeof ( bsse ) ) ;
 if ( ! x -> skip ) {
 int skippable_y , skippable_uv ;
 int64_t sseuv = INT64_MAX ;
 int64_t rdcosty = INT64_MAX ;
 vp9_subtract_plane ( x , bsize , 0 ) ;
 super_block_yrd ( cpi , x , rate_y , distortion_y , & skippable_y , psse , bsize , txfm_cache , ref_best_rd ) ;
 if ( * rate_y == INT_MAX ) {
 * rate2 = INT_MAX ;
 * distortion = INT64_MAX ;
 restore_dst_buf ( xd , orig_dst , orig_dst_stride ) ;
 return INT64_MAX ;
 }
 * rate2 += * rate_y ;
 * distortion += * distortion_y ;
 rdcosty = RDCOST ( x -> rdmult , x -> rddiv , * rate2 , * distortion ) ;
 rdcosty = MIN ( rdcosty , RDCOST ( x -> rdmult , x -> rddiv , 0 , * psse ) ) ;
 super_block_uvrd ( cpi , x , rate_uv , distortion_uv , & skippable_uv , & sseuv , bsize , ref_best_rd - rdcosty ) ;
 if ( * rate_uv == INT_MAX ) {
 * rate2 = INT_MAX ;
 * distortion = INT64_MAX ;
 restore_dst_buf ( xd , orig_dst , orig_dst_stride ) ;
 return INT64_MAX ;
 }
 * psse += sseuv ;
 * rate2 += * rate_uv ;
 * distortion += * distortion_uv ;
 * skippable = skippable_y && skippable_uv ;
 }
 if ( ! is_comp_pred ) single_skippable [ this_mode ] [ refs [ 0 ] ] = * skippable ;
 restore_dst_buf ( xd , orig_dst , orig_dst_stride ) ;
 return this_rd ;
 }
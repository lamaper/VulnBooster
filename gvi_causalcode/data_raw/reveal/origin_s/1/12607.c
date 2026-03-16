static void first_pass_motion_search ( VP9_COMP * cpi , MACROBLOCK * x , const MV * ref_mv , MV * best_mv , int * best_motion_err ) {
 MACROBLOCKD * const xd = & x -> e_mbd ;
 MV tmp_mv = {
 0 , 0 }
 ;
 MV ref_mv_full = {
 ref_mv -> row >> 3 , ref_mv -> col >> 3 }
 ;
 int num00 , tmp_err , n ;
 const BLOCK_SIZE bsize = xd -> mi [ 0 ] -> mbmi . sb_type ;
 vp9_variance_fn_ptr_t v_fn_ptr = cpi -> fn_ptr [ bsize ] ;
 const int new_mv_mode_penalty = 256 ;
 int step_param = 3 ;
 int further_steps = ( MAX_MVSEARCH_STEPS - 1 ) - step_param ;
 const int sr = get_search_range ( & cpi -> common ) ;
 step_param += sr ;
 further_steps -= sr ;
 v_fn_ptr . vf = get_block_variance_fn ( bsize ) ;
 tmp_err = cpi -> diamond_search_sad ( x , & cpi -> ss_cfg , & ref_mv_full , & tmp_mv , step_param , x -> sadperbit16 , & num00 , & v_fn_ptr , ref_mv ) ;
 if ( tmp_err < INT_MAX ) tmp_err = vp9_get_mvpred_var ( x , & tmp_mv , ref_mv , & v_fn_ptr , 1 ) ;
 if ( tmp_err < INT_MAX - new_mv_mode_penalty ) tmp_err += new_mv_mode_penalty ;
 if ( tmp_err < * best_motion_err ) {
 * best_motion_err = tmp_err ;
 * best_mv = tmp_mv ;
 }
 n = num00 ;
 num00 = 0 ;
 while ( n < further_steps ) {
 ++ n ;
 if ( num00 ) {
 -- num00 ;
 }
 else {
 tmp_err = cpi -> diamond_search_sad ( x , & cpi -> ss_cfg , & ref_mv_full , & tmp_mv , step_param + n , x -> sadperbit16 , & num00 , & v_fn_ptr , ref_mv ) ;
 if ( tmp_err < INT_MAX ) tmp_err = vp9_get_mvpred_var ( x , & tmp_mv , ref_mv , & v_fn_ptr , 1 ) ;
 if ( tmp_err < INT_MAX - new_mv_mode_penalty ) tmp_err += new_mv_mode_penalty ;
 if ( tmp_err < * best_motion_err ) {
 * best_motion_err = tmp_err ;
 * best_mv = tmp_mv ;
 }
 }
 }
 }
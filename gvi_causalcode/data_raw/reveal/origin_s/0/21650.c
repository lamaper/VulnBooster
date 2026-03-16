static unsigned int do_16x16_motion_iteration ( VP9_COMP * cpi , const MV * ref_mv , MV * dst_mv , int mb_row , int mb_col ) {
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 const MV_SPEED_FEATURES * const mv_sf = & cpi -> sf . mv ;
 const vp9_variance_fn_ptr_t v_fn_ptr = cpi -> fn_ptr [ BLOCK_16X16 ] ;
 const int tmp_col_min = x -> mv_col_min ;
 const int tmp_col_max = x -> mv_col_max ;
 const int tmp_row_min = x -> mv_row_min ;
 const int tmp_row_max = x -> mv_row_max ;
 MV ref_full ;
 int sad_list [ 5 ] ;
 int step_param = mv_sf -> reduce_first_step_size ;
 step_param = MIN ( step_param , MAX_MVSEARCH_STEPS - 2 ) ;
 vp9_set_mv_search_range ( x , ref_mv ) ;
 ref_full . col = ref_mv -> col >> 3 ;
 ref_full . row = ref_mv -> row >> 3 ;
 vp9_hex_search ( x , & ref_full , step_param , x -> errorperbit , 0 , cond_sad_list ( cpi , sad_list ) , & v_fn_ptr , 0 , ref_mv , dst_mv ) ;
 {
 int distortion ;
 unsigned int sse ;
 cpi -> find_fractional_mv_step ( x , dst_mv , ref_mv , cpi -> common . allow_high_precision_mv , x -> errorperbit , & v_fn_ptr , 0 , mv_sf -> subpel_iters_per_step , cond_sad_list ( cpi , sad_list ) , NULL , NULL , & distortion , & sse , NULL , 0 , 0 ) ;
 }
 xd -> mi [ 0 ] . src_mi -> mbmi . mode = NEWMV ;
 xd -> mi [ 0 ] . src_mi -> mbmi . mv [ 0 ] . as_mv = * dst_mv ;
 vp9_build_inter_predictors_sby ( xd , mb_row , mb_col , BLOCK_16X16 ) ;
 x -> mv_col_min = tmp_col_min ;
 x -> mv_col_max = tmp_col_max ;
 x -> mv_row_min = tmp_row_min ;
 x -> mv_row_max = tmp_row_max ;
 return vp9_sad16x16 ( x -> plane [ 0 ] . src . buf , x -> plane [ 0 ] . src . stride , xd -> plane [ 0 ] . dst . buf , xd -> plane [ 0 ] . dst . stride ) ;
 }
static void encode_frame_internal ( VP9_COMP * cpi ) {
 SPEED_FEATURES * const sf = & cpi -> sf ;
 RD_OPT * const rd_opt = & cpi -> rd ;
 MACROBLOCK * const x = & cpi -> mb ;
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 xd -> mi = cm -> mi ;
 xd -> mi [ 0 ] . src_mi = & xd -> mi [ 0 ] ;
 vp9_zero ( cm -> counts ) ;
 vp9_zero ( cpi -> coef_counts ) ;
 vp9_zero ( rd_opt -> comp_pred_diff ) ;
 vp9_zero ( rd_opt -> filter_diff ) ;
 vp9_zero ( rd_opt -> tx_select_diff ) ;
 vp9_zero ( rd_opt -> tx_select_threshes ) ;
 xd -> lossless = cm -> base_qindex == 0 && cm -> y_dc_delta_q == 0 && cm -> uv_dc_delta_q == 0 && cm -> uv_ac_delta_q == 0 ;
 cm -> tx_mode = select_tx_mode ( cpi ) ;
 x -> fwd_txm4x4 = xd -> lossless ? vp9_fwht4x4 : vp9_fdct4x4 ;
 x -> itxm_add = xd -> lossless ? vp9_iwht4x4_add : vp9_idct4x4_add ;
 if ( xd -> lossless ) {
 x -> optimize = 0 ;
 cm -> lf . filter_level = 0 ;
 cpi -> zbin_mode_boost_enabled = 0 ;
 }
 vp9_frame_init_quantizer ( cpi ) ;
 vp9_initialize_rd_consts ( cpi ) ;
 vp9_initialize_me_consts ( cpi , cm -> base_qindex ) ;
 init_encode_frame_mb_context ( cpi ) ;
 set_prev_mi ( cm ) ;
 x -> quant_fp = cpi -> sf . use_quant_fp ;
 vp9_zero ( x -> skip_txfm ) ;
 if ( sf -> use_nonrd_pick_mode ) {
 int i ;
 struct macroblock_plane * const p = x -> plane ;
 struct macroblockd_plane * const pd = xd -> plane ;
 PICK_MODE_CONTEXT * ctx = & cpi -> pc_root -> none ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 ++ i ) {
 p [ i ] . coeff = ctx -> coeff_pbuf [ i ] [ 0 ] ;
 p [ i ] . qcoeff = ctx -> qcoeff_pbuf [ i ] [ 0 ] ;
 pd [ i ] . dqcoeff = ctx -> dqcoeff_pbuf [ i ] [ 0 ] ;
 p [ i ] . eobs = ctx -> eobs_pbuf [ i ] [ 0 ] ;
 }
 vp9_zero ( x -> zcoeff_blk ) ;
 if ( sf -> partition_search_type == SOURCE_VAR_BASED_PARTITION ) source_var_based_partition_search_method ( cpi ) ;
 }
 {
 struct vpx_usec_timer emr_timer ;
 vpx_usec_timer_start ( & emr_timer ) ;

 input_fpmb_stats ( & cpi -> twopass . firstpass_mb_stats , cm , & cpi -> twopass . this_frame_mb_stats ) ;
 }

 vpx_usec_timer_mark ( & emr_timer ) ;
 cpi -> time_encode_sb_row += vpx_usec_timer_elapsed ( & emr_timer ) ;
 }
 sf -> skip_encode_frame = sf -> skip_encode_sb ? get_skip_encode_frame ( cm ) : 0 ;


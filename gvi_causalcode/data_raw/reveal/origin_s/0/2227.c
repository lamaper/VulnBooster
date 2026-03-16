static void update_state_rt ( VP9_COMP * cpi , PICK_MODE_CONTEXT * ctx , int mi_row , int mi_col , int bsize ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 MB_MODE_INFO * const mbmi = & xd -> mi [ 0 ] . src_mi -> mbmi ;
 const struct segmentation * const seg = & cm -> seg ;
 * ( xd -> mi [ 0 ] . src_mi ) = ctx -> mic ;
 xd -> mi [ 0 ] . src_mi = & xd -> mi [ 0 ] ;
 if ( ( cpi -> oxcf . aq_mode == CYCLIC_REFRESH_AQ ) && seg -> enabled ) {
 vp9_cyclic_refresh_update_segment ( cpi , & xd -> mi [ 0 ] . src_mi -> mbmi , mi_row , mi_col , bsize , 1 ) ;
 vp9_init_plane_quantizers ( cpi , x ) ;
 }
 if ( is_inter_block ( mbmi ) ) {
 vp9_update_mv_count ( cm , xd ) ;
 if ( cm -> interp_filter == SWITCHABLE ) {
 const int pred_ctx = vp9_get_pred_context_switchable_interp ( xd ) ;
 ++ cm -> counts . switchable_interp [ pred_ctx ] [ mbmi -> interp_filter ] ;
 }
 }
 x -> skip = ctx -> skip ;
 x -> skip_txfm [ 0 ] = mbmi -> segment_id ? 0 : ctx -> skip_txfm [ 0 ] ;
 }
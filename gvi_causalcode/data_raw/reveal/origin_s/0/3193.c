void vp9_setup_in_frame_q_adj ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 struct segmentation * const seg = & cm -> seg ;
 vp9_clear_system_state ( ) ;
 if ( cm -> frame_type == KEY_FRAME || cpi -> refresh_alt_ref_frame || ( cpi -> refresh_golden_frame && ! cpi -> rc . is_src_frame_alt_ref ) ) {
 int segment ;
 const int aq_strength = get_aq_c_strength ( cm -> base_qindex , cm -> bit_depth ) ;
 const int active_segments = aq_c_active_segments [ aq_strength ] ;
 vpx_memset ( cpi -> segmentation_map , 0 , cm -> mi_rows * cm -> mi_cols ) ;
 vpx_memset ( cpi -> complexity_map , 0 , cm -> mi_rows * cm -> mi_cols ) ;
 vp9_clearall_segfeatures ( seg ) ;
 if ( cpi -> rc . sb64_target_rate < 256 ) {
 vp9_disable_segmentation ( seg ) ;
 return ;
 }
 vp9_enable_segmentation ( seg ) ;
 seg -> abs_delta = SEGMENT_DELTADATA ;
 vp9_disable_segfeature ( seg , 0 , SEG_LVL_ALT_Q ) ;
 for ( segment = 1 ;
 segment < active_segments ;
 ++ segment ) {
 int qindex_delta = vp9_compute_qdelta_by_rate ( & cpi -> rc , cm -> frame_type , cm -> base_qindex , aq_c_q_adj_factor [ aq_strength ] [ segment ] , cm -> bit_depth ) ;
 if ( ( cm -> base_qindex != 0 ) && ( ( cm -> base_qindex + qindex_delta ) == 0 ) ) {
 qindex_delta = - cm -> base_qindex + 1 ;
 }
 if ( ( cm -> base_qindex + qindex_delta ) > 0 ) {
 vp9_enable_segfeature ( seg , segment , SEG_LVL_ALT_Q ) ;
 vp9_set_segdata ( seg , segment , SEG_LVL_ALT_Q , qindex_delta ) ;
 }
 }
 }
 }
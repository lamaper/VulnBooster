static void configure_static_seg_features ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 const RATE_CONTROL * const rc = & cpi -> rc ;
 struct segmentation * const seg = & cm -> seg ;
 int high_q = ( int ) ( rc -> avg_q > 48.0 ) ;
 int qi_delta ;
 if ( cm -> frame_type == KEY_FRAME ) {
 vpx_memset ( cpi -> segmentation_map , 0 , cm -> mi_rows * cm -> mi_cols ) ;
 seg -> update_map = 0 ;
 seg -> update_data = 0 ;
 cpi -> static_mb_pct = 0 ;
 vp9_disable_segmentation ( seg ) ;
 vp9_clearall_segfeatures ( seg ) ;
 }
 else if ( cpi -> refresh_alt_ref_frame ) {
 vpx_memset ( cpi -> segmentation_map , 0 , cm -> mi_rows * cm -> mi_cols ) ;
 seg -> update_map = 0 ;
 seg -> update_data = 0 ;
 cpi -> static_mb_pct = 0 ;
 vp9_disable_segmentation ( seg ) ;
 vp9_clearall_segfeatures ( seg ) ;
 vp9_update_mbgraph_stats ( cpi ) ;
 if ( seg -> enabled ) {
 seg -> update_map = 1 ;
 seg -> update_data = 1 ;
 qi_delta = vp9_compute_qdelta ( rc , rc -> avg_q , rc -> avg_q * 0.875 ) ;
 vp9_set_segdata ( seg , 1 , SEG_LVL_ALT_Q , qi_delta - 2 ) ;
 vp9_set_segdata ( seg , 1 , SEG_LVL_ALT_LF , - 2 ) ;
 vp9_enable_segfeature ( seg , 1 , SEG_LVL_ALT_Q ) ;
 vp9_enable_segfeature ( seg , 1 , SEG_LVL_ALT_LF ) ;
 seg -> abs_delta = SEGMENT_DELTADATA ;
 }
 }
 else if ( seg -> enabled ) {
 if ( rc -> frames_since_golden == 0 ) {
 if ( rc -> source_alt_ref_active ) {
 seg -> update_map = 0 ;
 seg -> update_data = 1 ;
 seg -> abs_delta = SEGMENT_DELTADATA ;
 qi_delta = vp9_compute_qdelta ( rc , rc -> avg_q , rc -> avg_q * 1.125 ) ;
 vp9_set_segdata ( seg , 1 , SEG_LVL_ALT_Q , qi_delta + 2 ) ;
 vp9_enable_segfeature ( seg , 1 , SEG_LVL_ALT_Q ) ;
 vp9_set_segdata ( seg , 1 , SEG_LVL_ALT_LF , - 2 ) ;
 vp9_enable_segfeature ( seg , 1 , SEG_LVL_ALT_LF ) ;
 if ( high_q || ( cpi -> static_mb_pct == 100 ) ) {
 vp9_set_segdata ( seg , 1 , SEG_LVL_REF_FRAME , ALTREF_FRAME ) ;
 vp9_enable_segfeature ( seg , 1 , SEG_LVL_REF_FRAME ) ;
 vp9_enable_segfeature ( seg , 1 , SEG_LVL_SKIP ) ;
 }
 }
 else {
 vp9_disable_segmentation ( seg ) ;
 vpx_memset ( cpi -> segmentation_map , 0 , cm -> mi_rows * cm -> mi_cols ) ;
 seg -> update_map = 0 ;
 seg -> update_data = 0 ;
 vp9_clearall_segfeatures ( seg ) ;
 }
 }
 else if ( rc -> is_src_frame_alt_ref ) {
 vp9_enable_segfeature ( seg , 0 , SEG_LVL_REF_FRAME ) ;
 vp9_enable_segfeature ( seg , 1 , SEG_LVL_REF_FRAME ) ;
 vp9_clear_segdata ( seg , 0 , SEG_LVL_REF_FRAME ) ;
 vp9_set_segdata ( seg , 0 , SEG_LVL_REF_FRAME , ALTREF_FRAME ) ;
 vp9_clear_segdata ( seg , 1 , SEG_LVL_REF_FRAME ) ;
 vp9_set_segdata ( seg , 1 , SEG_LVL_REF_FRAME , ALTREF_FRAME ) ;
 if ( high_q ) {
 vp9_enable_segfeature ( seg , 0 , SEG_LVL_SKIP ) ;
 vp9_enable_segfeature ( seg , 1 , SEG_LVL_SKIP ) ;
 }
 seg -> update_data = 1 ;
 }
 else {
 seg -> update_map = 0 ;
 seg -> update_data = 0 ;
 }
 }
 }
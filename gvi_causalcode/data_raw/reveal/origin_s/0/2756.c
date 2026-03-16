void vp9_vaq_frame_setup ( VP9_COMP * cpi ) {
 VP9_COMMON * cm = & cpi -> common ;
 struct segmentation * seg = & cm -> seg ;
 const double base_q = vp9_convert_qindex_to_q ( cm -> base_qindex , cm -> bit_depth ) ;
 const int base_rdmult = vp9_compute_rd_mult ( cpi , cm -> base_qindex + cm -> y_dc_delta_q ) ;
 int i ;
 if ( cm -> frame_type == KEY_FRAME || cpi -> refresh_alt_ref_frame || ( cpi -> refresh_golden_frame && ! cpi -> rc . is_src_frame_alt_ref ) ) {
 vp9_enable_segmentation ( seg ) ;
 vp9_clearall_segfeatures ( seg ) ;
 seg -> abs_delta = SEGMENT_DELTADATA ;
 vp9_clear_system_state ( ) ;
 for ( i = ENERGY_MIN ;
 i <= ENERGY_MAX ;
 i ++ ) {
 int qindex_delta , segment_rdmult ;
 if ( Q_RATIO ( i ) == 1 ) {
 RDMULT_RATIO ( i ) = 1 ;
 continue ;
 }
 qindex_delta = vp9_compute_qdelta ( & cpi -> rc , base_q , base_q * Q_RATIO ( i ) , cm -> bit_depth ) ;
 vp9_set_segdata ( seg , SEGMENT_ID ( i ) , SEG_LVL_ALT_Q , qindex_delta ) ;
 vp9_enable_segfeature ( seg , SEGMENT_ID ( i ) , SEG_LVL_ALT_Q ) ;
 segment_rdmult = vp9_compute_rd_mult ( cpi , cm -> base_qindex + qindex_delta + cm -> y_dc_delta_q ) ;
 RDMULT_RATIO ( i ) = ( double ) segment_rdmult / base_rdmult ;
 }
 }
 }
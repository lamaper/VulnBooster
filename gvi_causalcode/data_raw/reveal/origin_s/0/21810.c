static void encode_without_recode_loop ( VP9_COMP * cpi , int q ) {
 VP9_COMMON * const cm = & cpi -> common ;
 vp9_clear_system_state ( ) ;
 vp9_set_quantizer ( cm , q ) ;
 setup_frame ( cpi ) ;
 if ( cpi -> oxcf . aq_mode == VARIANCE_AQ ) {
 vp9_vaq_frame_setup ( cpi ) ;
 }
 else if ( cpi -> oxcf . aq_mode == COMPLEXITY_AQ ) {
 vp9_setup_in_frame_q_adj ( cpi ) ;
 }
 else if ( cpi -> oxcf . aq_mode == CYCLIC_REFRESH_AQ ) {
 vp9_cyclic_refresh_setup ( cpi ) ;
 }
 vp9_encode_frame ( cpi ) ;
 vp9_clear_system_state ( ) ;
 }
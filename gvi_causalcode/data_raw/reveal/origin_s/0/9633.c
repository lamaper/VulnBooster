static void setup_frame ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 if ( frame_is_intra_only ( cm ) || cm -> error_resilient_mode ) {
 vp9_setup_past_independence ( cm ) ;
 }
 else {
 if ( ! cpi -> use_svc ) cm -> frame_context_idx = cpi -> refresh_alt_ref_frame ;
 }
 if ( cm -> frame_type == KEY_FRAME ) {
 if ( ! is_two_pass_svc ( cpi ) ) cpi -> refresh_golden_frame = 1 ;
 cpi -> refresh_alt_ref_frame = 1 ;
 vp9_zero ( cpi -> interp_filter_selected ) ;
 }
 else {
 cm -> fc = cm -> frame_contexts [ cm -> frame_context_idx ] ;
 vp9_zero ( cpi -> interp_filter_selected [ 0 ] ) ;
 }
 }
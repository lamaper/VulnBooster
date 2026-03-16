void vp8_loopfilter_frame ( VP8_COMP * cpi , VP8_COMMON * cm ) {
 const FRAME_TYPE frame_type = cm -> frame_type ;
 if ( cm -> no_lpf ) {
 cm -> filter_level = 0 ;
 }
 else {
 struct vpx_usec_timer timer ;
 vp8_clear_system_state ( ) ;
 vpx_usec_timer_start ( & timer ) ;
 if ( cpi -> sf . auto_filter == 0 ) vp8cx_pick_filter_level_fast ( cpi -> Source , cpi ) ;
 else vp8cx_pick_filter_level ( cpi -> Source , cpi ) ;
 if ( cm -> filter_level > 0 ) {
 vp8cx_set_alt_lf_level ( cpi , cm -> filter_level ) ;
 }
 vpx_usec_timer_mark ( & timer ) ;
 cpi -> time_pick_lpf += vpx_usec_timer_elapsed ( & timer ) ;
 }


 vp8_loop_filter_frame ( cm , & cpi -> mb . e_mbd , frame_type ) ;
 }
 vp8_yv12_extend_frame_borders ( cm -> frame_to_show ) ;
 }
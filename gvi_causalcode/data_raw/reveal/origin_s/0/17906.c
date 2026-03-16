static void loopfilter_frame ( VP9_COMP * cpi , VP9_COMMON * cm ) {
 MACROBLOCKD * xd = & cpi -> mb . e_mbd ;
 struct loopfilter * lf = & cm -> lf ;
 if ( xd -> lossless ) {
 lf -> filter_level = 0 ;
 }
 else {
 struct vpx_usec_timer timer ;
 vp9_clear_system_state ( ) ;
 vpx_usec_timer_start ( & timer ) ;
 vp9_pick_filter_level ( cpi -> Source , cpi , cpi -> sf . lpf_pick ) ;
 vpx_usec_timer_mark ( & timer ) ;
 cpi -> time_pick_lpf += vpx_usec_timer_elapsed ( & timer ) ;
 }
 if ( lf -> filter_level > 0 ) {
 vp9_loop_filter_frame ( cm -> frame_to_show , cm , xd , lf -> filter_level , 0 , 0 ) ;
 }
 vp9_extend_frame_inner_borders ( cm -> frame_to_show ) ;
 }
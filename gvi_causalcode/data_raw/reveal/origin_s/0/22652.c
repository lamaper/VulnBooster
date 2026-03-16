static void set_mv_search_params ( VP9_COMP * cpi ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 const unsigned int max_mv_def = MIN ( cm -> width , cm -> height ) ;
 cpi -> mv_step_param = vp9_init_search_range ( max_mv_def ) ;
 if ( cpi -> sf . mv . auto_mv_step_size ) {
 if ( frame_is_intra_only ( cm ) ) {
 cpi -> max_mv_magnitude = max_mv_def ;
 }
 else {
 if ( cm -> show_frame ) cpi -> mv_step_param = vp9_init_search_range ( MIN ( max_mv_def , 2 * cpi -> max_mv_magnitude ) ) ;
 cpi -> max_mv_magnitude = 0 ;
 }
 }
 }
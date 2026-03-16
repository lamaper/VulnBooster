static void source_var_based_partition_search_method ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 SPEED_FEATURES * const sf = & cpi -> sf ;
 if ( cm -> frame_type == KEY_FRAME ) {
 sf -> partition_search_type = SEARCH_PARTITION ;
 }
 else if ( cm -> intra_only ) {
 sf -> partition_search_type = FIXED_PARTITION ;
 }
 else {
 if ( cm -> last_width != cm -> width || cm -> last_height != cm -> height ) {
 if ( cpi -> source_diff_var ) vpx_free ( cpi -> source_diff_var ) ;
 CHECK_MEM_ERROR ( cm , cpi -> source_diff_var , vpx_calloc ( cm -> MBs , sizeof ( diff ) ) ) ;
 }
 if ( ! cpi -> frames_till_next_var_check ) cpi -> frames_till_next_var_check = set_var_thresh_from_histogram ( cpi ) ;
 if ( cpi -> frames_till_next_var_check > 0 ) {
 sf -> partition_search_type = FIXED_PARTITION ;
 cpi -> frames_till_next_var_check -- ;
 }
 }
 }
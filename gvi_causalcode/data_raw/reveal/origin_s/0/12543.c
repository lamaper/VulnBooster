static void check_initial_width ( VP9_COMP * cpi , int subsampling_x , int subsampling_y ) {
 VP9_COMMON * const cm = & cpi -> common ;
 if ( ! cpi -> initial_width ) {
 cm -> subsampling_x = subsampling_x ;
 cm -> subsampling_y = subsampling_y ;
 alloc_raw_frame_buffers ( cpi ) ;
 alloc_ref_frame_buffers ( cpi ) ;
 alloc_util_frame_buffers ( cpi ) ;
 init_motion_estimation ( cpi ) ;
 cpi -> initial_width = cm -> width ;
 cpi -> initial_height = cm -> height ;
 }
 }
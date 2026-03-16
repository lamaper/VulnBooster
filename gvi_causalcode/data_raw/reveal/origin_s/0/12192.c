static int try_filter_frame ( const YV12_BUFFER_CONFIG * sd , VP9_COMP * const cpi , int filt_level , int partial_frame ) {
 VP9_COMMON * const cm = & cpi -> common ;
 int filt_err ;
 vp9_loop_filter_frame ( cm -> frame_to_show , cm , & cpi -> mb . e_mbd , filt_level , 1 , partial_frame ) ;
 filt_err = vp9_get_y_sse ( sd , cm -> frame_to_show ) ;
 vpx_yv12_copy_y ( & cpi -> last_frame_uf , cm -> frame_to_show ) ;
 return filt_err ;
 }
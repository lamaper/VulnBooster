static double calc_frame_boost ( VP9_COMP * cpi , const FIRSTPASS_STATS * this_frame , double this_frame_mv_in_out , double max_boost ) {
 double frame_boost ;
 frame_boost = ( BASELINE_ERR_PER_MB * cpi -> common . MBs ) / DOUBLE_DIVIDE_CHECK ( this_frame -> coded_error ) ;
 frame_boost = frame_boost * BOOST_FACTOR ;
 if ( this_frame_mv_in_out > 0.0 ) frame_boost += frame_boost * ( this_frame_mv_in_out * 2.0 ) ;
 else frame_boost += frame_boost * ( this_frame_mv_in_out / 2.0 ) ;
 return MIN ( frame_boost , max_boost ) ;
 }
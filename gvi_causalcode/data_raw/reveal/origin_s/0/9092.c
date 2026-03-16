static void log_frame_info ( VP9_COMMON * cm , const char * str , FILE * f ) {
 fprintf ( f , "%s" , str ) ;
 fprintf ( f , "(Frame %d, Show:%d, Q:%d): \n" , cm -> current_video_frame , cm -> show_frame , cm -> base_qindex ) ;
 }
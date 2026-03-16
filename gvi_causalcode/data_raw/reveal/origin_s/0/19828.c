int vp9_loop_filter_worker ( LFWorkerData * const lf_data , void * unused ) {
 ( void ) unused ;
 vp9_loop_filter_rows ( lf_data -> frame_buffer , lf_data -> cm , lf_data -> planes , lf_data -> start , lf_data -> stop , lf_data -> y_only ) ;
 return 1 ;
 }
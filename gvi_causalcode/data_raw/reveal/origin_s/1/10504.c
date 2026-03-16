int vp9_loop_filter_worker ( void * arg1 , void * arg2 ) {
 LFWorkerData * const lf_data = ( LFWorkerData * ) arg1 ;
 ( void ) arg2 ;
 vp9_loop_filter_rows ( lf_data -> frame_buffer , lf_data -> cm , lf_data -> planes , lf_data -> start , lf_data -> stop , lf_data -> y_only ) ;
 return 1 ;
 }
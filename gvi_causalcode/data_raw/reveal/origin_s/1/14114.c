static int loop_filter_row_worker ( void * arg1 , void * arg2 ) {
 TileWorkerData * const tile_data = ( TileWorkerData * ) arg1 ;
 LFWorkerData * const lf_data = & tile_data -> lfdata ;
 ( void ) arg2 ;
 loop_filter_rows_mt ( lf_data -> frame_buffer , lf_data -> cm , lf_data -> planes , lf_data -> start , lf_data -> stop , lf_data -> y_only , lf_data -> lf_sync , lf_data -> num_lf_workers ) ;
 return 1 ;
 }
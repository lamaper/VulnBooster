static int http_config_cb ( const char * , RecDataT , RecData , void * ) {
 ink_atomic_increment ( ( int * ) & http_config_changes , 1 ) ;
 INK_MEMORY_BARRIER ;
 eventProcessor . schedule_in ( http_config_cont , HRTIME_SECONDS ( 1 ) , ET_CALL ) ;
 return 0 ;
 }
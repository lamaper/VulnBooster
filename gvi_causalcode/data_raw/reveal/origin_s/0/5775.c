static void * pthread_start_func ( void * ) {
 TSThread temp_thread = nullptr ;
 temp_thread = TSThreadInit ( ) ;
 if ( ! temp_thread ) {
 SDK_RPRINT ( SDK_ThreadInit_test , "TSThreadInit" , "TestCase2" , TC_FAIL , "can't init thread" ) ;
 thread_init_err_count ++ ;
 }
 else {
 SDK_RPRINT ( SDK_ThreadInit_test , "TSThreadInit" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 if ( temp_thread ) {
 TSThreadDestroy ( temp_thread ) ;
 }
 if ( thread_init_err_count > 0 ) {
 * SDK_ThreadInit_pstatus = REGRESSION_TEST_FAILED ;
 }
 else {
 * SDK_ThreadInit_pstatus = REGRESSION_TEST_PASSED ;
 }
 return nullptr ;
 }
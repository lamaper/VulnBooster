static void * thread_create_handler ( void * ) {
 TSThread athread ;
 sleep ( 10 ) ;
 athread = TSThreadSelf ( ) ;
 if ( athread == nullptr ) {
 thread_err_count ++ ;
 SDK_RPRINT ( SDK_Thread_test , "TSThreadCreate" , "TestCase2" , TC_FAIL , "can't get thread" ) ;
 }
 else {
 SDK_RPRINT ( SDK_Thread_test , "TSThreadCreate" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 if ( thread_err_count > 0 ) {
 * SDK_Thread_pstatus = REGRESSION_TEST_FAILED ;
 }
 else {
 * SDK_Thread_pstatus = REGRESSION_TEST_PASSED ;
 }
 return nullptr ;
 }
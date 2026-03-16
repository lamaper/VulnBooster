REGRESSION_TEST ( SDK_API_TSThread ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 SDK_Thread_test = test ;
 SDK_Thread_pstatus = pstatus ;
 TSThread curr_thread = nullptr ;
 pthread_t curr_tid ;
 curr_tid = pthread_self ( ) ;
 curr_thread = TSThreadSelf ( ) ;
 if ( curr_thread == nullptr ) {
 SDK_RPRINT ( test , "TSThreadSelf" , "TestCase1" , TC_FAIL , "can't get the current thread" ) ;
 thread_err_count ++ ;
 }
 else {
 SDK_RPRINT ( test , "TSThreadSelf" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 TSThread created_thread = TSThreadCreate ( thread_create_handler , ( void * ) ( intptr_t ) curr_tid ) ;
 if ( created_thread == nullptr ) {
 thread_err_count ++ ;
 SDK_RPRINT ( test , "TSThreadCreate" , "TestCase1" , TC_FAIL , "can't create thread" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSThreadCreate" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 }
REGRESSION_TEST ( SDK_API_TSThreadInit ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 SDK_ThreadInit_test = test ;
 SDK_ThreadInit_pstatus = pstatus ;
 pthread_t curr_tid , new_tid ;
 curr_tid = pthread_self ( ) ;
 int ret ;
 errno = 0 ;
 ret = pthread_create ( & new_tid , nullptr , pthread_start_func , ( void * ) ( intptr_t ) curr_tid ) ;
 if ( ret != 0 ) {
 thread_init_err_count ++ ;
 SDK_RPRINT ( test , "TSThreadInit" , "TestCase1" , TC_FAIL , "can't create pthread" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSThreadInit" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 }
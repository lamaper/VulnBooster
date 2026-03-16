REGRESSION_TEST ( SDK_API_TSContSchedule ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 SDK_ContSchedule_test = test ;
 SDK_ContSchedule_pstatus = pstatus ;
 TSCont contp = TSContCreate ( cont_schedule_handler , TSMutexCreate ( ) ) ;
 TSCont contp2 = TSContCreate ( cont_schedule_handler , TSMutexCreate ( ) ) ;
 TSContSchedule ( contp , 0 , TS_THREAD_POOL_DEFAULT ) ;
 TSContSchedule ( contp2 , 10 , TS_THREAD_POOL_DEFAULT ) ;
 }
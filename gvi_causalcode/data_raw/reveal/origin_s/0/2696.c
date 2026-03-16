REGRESSION_TEST ( SDK_API_TSActionCancel ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 SDK_ActionCancel_test = test ;
 SDK_ActionCancel_pstatus = pstatus ;
 TSMutex cont_mutex = TSMutexCreate ( ) ;
 TSCont contp = TSContCreate ( action_cancel_handler , cont_mutex ) ;
 TSAction actionp = TSContSchedule ( contp , 10000 , TS_THREAD_POOL_DEFAULT ) ;
 TSMutexLock ( cont_mutex ) ;
 if ( TSActionDone ( actionp ) ) {
 * pstatus = REGRESSION_TEST_FAILED ;
 TSMutexUnlock ( cont_mutex ) ;
 return ;
 }
 else {
 TSActionCancel ( actionp ) ;
 }
 TSMutexUnlock ( cont_mutex ) ;
 TSContSchedule ( contp , 0 , TS_THREAD_POOL_DEFAULT ) ;
 }
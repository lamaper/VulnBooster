REGRESSION_TEST ( SDK_API_TSMutexCreate ) ( RegressionTest * test , int , int * pstatus ) {
 bool test_passed = false ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 TSMutex mutexp = TSMutexCreate ( ) ;
 TSMutexLock ( mutexp ) ;
 TSReturnCode lock = TS_ERROR ;
 TSMutexLockTry ( mutexp ) ;
 lock = TSMutexLockTry ( mutexp ) ;
 if ( TS_SUCCESS == lock ) {
 SDK_RPRINT ( test , "TSMutexCreate" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMutexLock" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMutexLockTry" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMutexCreate" , "TestCase1" , TC_FAIL , "mutex can't be grabbed twice from the same thread" ) ;
 SDK_RPRINT ( test , "TSMutexLock" , "TestCase1" , TC_FAIL , "mutex can't be grabbed twice from the same thread" ) ;
 SDK_RPRINT ( test , "TSMutexLockTry" , "TestCase1" , TC_FAIL , "mutex can't be grabbed twice from the same thread" ) ;
 }
 TSMutexUnlock ( mutexp ) ;
 SDK_RPRINT ( test , "TSMutexUnLock" , "TestCase1" , TC_PASS , "ok" ) ;
 if ( test_passed ) {
 * pstatus = REGRESSION_TEST_PASSED ;
 }
 else {
 * pstatus = REGRESSION_TEST_FAILED ;
 }
 }
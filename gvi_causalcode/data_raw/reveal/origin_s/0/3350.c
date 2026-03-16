REGRESSION_TEST ( SDK_API_TSContCreate ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 SDK_ContCreate_test = test ;
 SDK_ContCreate_pstatus = pstatus ;
 TSMutex mutexp = TSMutexCreate ( ) ;
 TSCont contp = TSContCreate ( cont_handler , mutexp ) ;
 if ( TS_SUCCESS == TSMutexLockTry ( mutexp ) ) {
 TSContCall ( contp , ( TSEvent ) 0 , nullptr ) ;
 TSMutexUnlock ( mutexp ) ;
 }
 else {
 SDK_RPRINT ( SDK_ContCreate_test , "TSContCreate" , "TestCase1" , TC_FAIL , "continuation creation has problems" ) ;
 SDK_RPRINT ( SDK_ContCreate_test , "TSContCall" , "TestCase1" , TC_FAIL , "continuation has problems" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 }
 TSContDestroy ( contp ) ;
 }
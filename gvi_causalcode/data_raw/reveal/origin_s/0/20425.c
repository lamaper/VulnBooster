int cont_handler ( TSCont , TSEvent , void * ) {
 SDK_RPRINT ( SDK_ContCreate_test , "TSContCreate" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( SDK_ContCreate_test , "TSContCall" , "TestCase1" , TC_PASS , "ok" ) ;
 * SDK_ContCreate_pstatus = REGRESSION_TEST_PASSED ;
 return 0 ;
 }
int cont_data_handler ( TSCont contp , TSEvent , void * ) {
 MyData * my_data = ( MyData * ) TSContDataGet ( contp ) ;
 if ( my_data -> data1 == 1 && my_data -> data2 == 2 ) {
 SDK_RPRINT ( SDK_ContData_test , "TSContDataSet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( SDK_ContData_test , "TSContDataGet" , "TestCase1" , TC_PASS , "ok" ) ;
 * SDK_ContData_pstatus = REGRESSION_TEST_PASSED ;
 }
 else {
 SDK_RPRINT ( SDK_ContData_test , "TSContDataSet" , "TestCase1" , TC_FAIL , "bad data" ) ;
 SDK_RPRINT ( SDK_ContData_test , "TSContDataGet" , "TestCase1" , TC_FAIL , "bad data" ) ;
 * SDK_ContData_pstatus = REGRESSION_TEST_FAILED ;
 }
 TSfree ( my_data ) ;
 TSContDestroy ( contp ) ;
 return 0 ;
 }
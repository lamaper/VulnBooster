REGRESSION_TEST ( SDK_API_TSContMutexGet ) ( RegressionTest * test , int , int * pstatus ) {
 bool test_passed = false ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 TSMutex mutexp_input ;
 TSMutex mutexp_output ;
 TSCont contp ;
 mutexp_input = TSMutexCreate ( ) ;
 contp = TSContCreate ( cont_handler , mutexp_input ) ;
 mutexp_output = TSContMutexGet ( contp ) ;
 if ( mutexp_input == mutexp_output ) {
 SDK_RPRINT ( test , "TSContMutexGet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed = true ;
 }
 else {
 SDK_RPRINT ( test , "TSContMutexGet" , "TestCase1" , TC_FAIL , "Continutation's mutex corrupted" ) ;
 }
 * pstatus = ( ( test_passed == true ) ? REGRESSION_TEST_PASSED : REGRESSION_TEST_FAILED ) ;
 TSContDestroy ( contp ) ;
 }
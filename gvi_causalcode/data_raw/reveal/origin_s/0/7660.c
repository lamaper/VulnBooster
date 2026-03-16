int action_cancel_handler ( TSCont contp , TSEvent event , void * ) {
 if ( event == TS_EVENT_IMMEDIATE ) {
 SDK_RPRINT ( SDK_ActionCancel_test , "TSActionCancel" , "TestCase1" , TC_PASS , "ok" ) ;
 * SDK_ActionCancel_pstatus = REGRESSION_TEST_PASSED ;
 }
 else if ( event == TS_EVENT_TIMEOUT ) {
 SDK_RPRINT ( SDK_ActionCancel_test , "TSActionCancel" , "TestCase1" , TC_FAIL , "bad action" ) ;
 * SDK_ActionCancel_pstatus = REGRESSION_TEST_FAILED ;
 }
 else {
 SDK_RPRINT ( SDK_ActionCancel_test , "TSActionCancel" , "TestCase1" , TC_FAIL , "bad event" ) ;
 * SDK_ActionCancel_pstatus = REGRESSION_TEST_FAILED ;
 }
 TSContDestroy ( contp ) ;
 return 0 ;
 }
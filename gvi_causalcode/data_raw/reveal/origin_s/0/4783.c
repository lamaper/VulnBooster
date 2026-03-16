int cont_schedule_handler ( TSCont contp , TSEvent event , void * ) {
 if ( event == TS_EVENT_IMMEDIATE ) {
 SDK_RPRINT ( SDK_ContSchedule_test , "TSContSchedule" , "TestCase1" , TC_PASS , "ok" ) ;
 tc1_count ++ ;
 }
 else if ( event == TS_EVENT_TIMEOUT ) {
 SDK_RPRINT ( SDK_ContSchedule_test , "TSContSchedule" , "TestCase2" , TC_PASS , "ok" ) ;
 tc2_count ++ ;
 }
 else {
 SDK_RPRINT ( SDK_ContSchedule_test , "TSContSchedule" , "TestCase1|2" , TC_FAIL , "received unexpected event number %d" , event ) ;
 * SDK_ContSchedule_pstatus = REGRESSION_TEST_FAILED ;
 return 0 ;
 }
 if ( ( tc1_count == 1 ) && ( tc2_count == 1 ) ) {
 * SDK_ContSchedule_pstatus = REGRESSION_TEST_PASSED ;
 }
 else if ( tc1_count + tc2_count >= 2 ) {
 * SDK_ContSchedule_pstatus = REGRESSION_TEST_FAILED ;
 }
 TSContDestroy ( contp ) ;
 return 0 ;
 }
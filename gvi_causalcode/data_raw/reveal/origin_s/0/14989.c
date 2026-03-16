REGRESSION_TEST ( SDK_API_DEBUG_NAME_LOOKUPS ) ( RegressionTest * test , int , int * pstatus ) {
 bool success = true ;
 const char state_name [ ] = "INACTIVE_TIMEOUT" ;
 const char hook_name [ ] = "TS_HTTP_READ_RESPONSE_HDR_HOOK" ;
 const char event_name [ ] = "VC_EVENT_IMMEDIATE" ;
 const char * str ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 str = TSHttpServerStateNameLookup ( TS_SRVSTATE_INACTIVE_TIMEOUT ) ;
 if ( ( strlen ( str ) != strlen ( state_name ) || strcmp ( str , state_name ) ) ) {
 SDK_RPRINT ( test , "TSHttpServerStateNameLookup" , "TestCase1" , TC_FAIL , "Failed on %d, expected %s, got %s" , TS_SRVSTATE_INACTIVE_TIMEOUT , state_name , str ) ;
 success = false ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpServerStateNameLookup" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 str = TSHttpHookNameLookup ( TS_HTTP_READ_RESPONSE_HDR_HOOK ) ;
 if ( ( strlen ( str ) != strlen ( hook_name ) || strcmp ( str , hook_name ) ) ) {
 SDK_RPRINT ( test , "TSHttpHookNameLookup" , "TestCase1" , TC_FAIL , "Failed on %d, expected %s, got %s" , TS_HTTP_READ_RESPONSE_HDR_HOOK , hook_name , str ) ;
 success = false ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHookNameLookup" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 str = TSHttpEventNameLookup ( TS_EVENT_IMMEDIATE ) ;
 if ( ( strlen ( str ) != strlen ( event_name ) || strcmp ( str , event_name ) ) ) {
 SDK_RPRINT ( test , "TSHttpEventNameLookup" , "TestCase1" , TC_FAIL , "Failed on %d, expected %s, got %s" , TS_EVENT_IMMEDIATE , hook_name , str ) ;
 success = false ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpEventNameLookup" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 * pstatus = success ? REGRESSION_TEST_PASSED : REGRESSION_TEST_FAILED ;
 return ;
 }
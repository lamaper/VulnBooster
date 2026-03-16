REGRESSION_TEST ( SDK_API_TSTrafficServerVersionGet ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 const char * ts_version = TSTrafficServerVersionGet ( ) ;
 if ( ! ts_version ) {
 SDK_RPRINT ( test , "TSTrafficServerVersionGet" , "TestCase1" , TC_FAIL , "can't get traffic server version" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 int major_ts_version = 0 ;
 int minor_ts_version = 0 ;
 int patch_ts_version = 0 ;
 if ( sscanf ( ts_version , "%d.%d.%d" , & major_ts_version , & minor_ts_version , & patch_ts_version ) != 3 ) {
 SDK_RPRINT ( test , "TSTrafficServerVersionGet" , "TestCase2" , TC_FAIL , "traffic server version format is incorrect" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 if ( major_ts_version < 2 ) {
 SDK_RPRINT ( test , "TSTrafficServerVersionGet" , "TestCase3" , TC_FAIL , "traffic server major version is incorrect" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 SDK_RPRINT ( test , "TSTrafficServerVersionGet" , "TestCase1" , TC_PASS , "ok" ) ;
 * pstatus = REGRESSION_TEST_PASSED ;
 return ;
 }
EXCLUSIVE_REGRESSION_TEST ( SDK_API_HttpSsn ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 TSCont cont = TSContCreate ( ssn_handler , TSMutexCreate ( ) ) ;
 if ( cont == nullptr ) {
 SDK_RPRINT ( test , "TSHttpSsn" , "TestCase1" , TC_FAIL , "Unable to create Continuation." ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 ContData * socktest = ( ContData * ) TSmalloc ( sizeof ( ContData ) ) ;
 socktest -> test = test ;
 socktest -> pstatus = pstatus ;
 socktest -> test_passed_ssn_hook_add = 0 ;
 socktest -> test_passed_ssn_reenable = 0 ;
 socktest -> test_passed_txn_ssn_get = 0 ;
 socktest -> test_passed_txn_hook_add = 0 ;
 socktest -> test_passed_txn_error_body_set = 0 ;
 socktest -> test_passed_Parent_Proxy = false ;
 socktest -> magic = MAGIC_ALIVE ;
 TSContDataSet ( cont , socktest ) ;
 TSHttpHookAdd ( TS_HTTP_SSN_START_HOOK , cont ) ;
 socktest -> browser = synclient_txn_create ( ) ;
 char * request = generate_request ( 3 ) ;
 synclient_txn_send_request ( socktest -> browser , request ) ;
 TSfree ( request ) ;
 if ( socktest -> browser -> status == REQUEST_INPROGRESS ) {
 TSContSchedule ( cont , 25 , TS_THREAD_POOL_DEFAULT ) ;
 }
 return ;
 }
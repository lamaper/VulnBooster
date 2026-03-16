EXCLUSIVE_REGRESSION_TEST ( SDK_API_HttpAltInfo ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 TSCont cont = TSContCreate ( altinfo_hook_handler , TSMutexCreate ( ) ) ;
 if ( cont == nullptr ) {
 SDK_RPRINT ( test , "TSHttpSsn" , "TestCase1" , TC_FAIL , "Unable to create Continuation." ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 TSHttpHookAdd ( TS_HTTP_READ_REQUEST_HDR_HOOK , cont ) ;
 AltInfoTestData * socktest = ( AltInfoTestData * ) TSmalloc ( sizeof ( AltInfoTestData ) ) ;
 socktest -> test = test ;
 socktest -> pstatus = pstatus ;
 socktest -> test_passed_txn_alt_info_client_req_get = true ;
 socktest -> test_passed_txn_alt_info_cached_req_get = true ;
 socktest -> test_passed_txn_alt_info_cached_resp_get = true ;
 socktest -> test_passed_txn_alt_info_quality_set = true ;
 socktest -> run_at_least_once = false ;
 socktest -> first_time = true ;
 socktest -> magic = MAGIC_ALIVE ;
 TSContDataSet ( cont , socktest ) ;
 socktest -> os = synserver_create ( SYNSERVER_LISTEN_PORT ) ;
 synserver_start ( socktest -> os ) ;
 socktest -> browser1 = synclient_txn_create ( ) ;
 socktest -> browser2 = synclient_txn_create ( ) ;
 socktest -> browser3 = synclient_txn_create ( ) ;
 socktest -> request1 = generate_request ( 6 ) ;
 socktest -> request2 = generate_request ( 7 ) ;
 socktest -> request3 = generate_request ( 8 ) ;
 synclient_txn_send_request ( socktest -> browser1 , socktest -> request1 ) ;
 synclient_txn_send_request ( socktest -> browser2 , socktest -> request2 ) ;
 TSContSchedule ( cont , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return ;
 }
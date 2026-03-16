EXCLUSIVE_REGRESSION_TEST ( SDK_API_HttpTxnCache ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 TSCont cont = TSContCreate ( cache_hook_handler , TSMutexCreate ( ) ) ;
 if ( cont == nullptr ) {
 SDK_RPRINT ( test , "TSHttpSsn" , "TestCase1" , TC_FAIL , "Unable to create Continuation." ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 CacheTestData * socktest = ( CacheTestData * ) TSmalloc ( sizeof ( CacheTestData ) ) ;
 socktest -> test = test ;
 socktest -> pstatus = pstatus ;
 socktest -> test_passed_txn_cached_req_get = false ;
 socktest -> test_passed_txn_cached_resp_get = false ;
 socktest -> first_time = true ;
 socktest -> magic = MAGIC_ALIVE ;
 TSContDataSet ( cont , socktest ) ;
 TSHttpHookAdd ( TS_HTTP_READ_REQUEST_HDR_HOOK , cont ) ;
 TSHttpHookAdd ( TS_HTTP_READ_CACHE_HDR_HOOK , cont ) ;
 TSHttpHookAdd ( TS_HTTP_CACHE_LOOKUP_COMPLETE_HOOK , cont ) ;
 socktest -> os = synserver_create ( SYNSERVER_LISTEN_PORT ) ;
 synserver_start ( socktest -> os ) ;
 socktest -> browser1 = synclient_txn_create ( ) ;
 socktest -> browser2 = synclient_txn_create ( ) ;
 socktest -> request = generate_request ( 2 ) ;
 synclient_txn_send_request ( socktest -> browser1 , socktest -> request ) ;
 TSContSchedule ( cont , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return ;
 }
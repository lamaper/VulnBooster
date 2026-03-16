EXCLUSIVE_REGRESSION_TEST ( SDK_API_HttpTxnTransform ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 Debug ( UTDBG_TAG "_transform" , "Starting test" ) ;
 TSCont cont = TSContCreate ( transform_hook_handler , TSMutexCreate ( ) ) ;
 if ( cont == nullptr ) {
 SDK_RPRINT ( test , "TSHttpSsn" , "TestCase1" , TC_FAIL , "Unable to create Continuation." ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 TransformTestData * socktest = ( TransformTestData * ) TSmalloc ( sizeof ( TransformTestData ) ) ;
 socktest -> test = test ;
 socktest -> pstatus = pstatus ;
 socktest -> test_passed_txn_transform_resp_get = true ;
 socktest -> test_passed_txn_transformed_resp_cache = false ;
 socktest -> test_passed_txn_transformed_resp_cache = false ;
 socktest -> test_passed_transform_create = false ;
 socktest -> req_no = 1 ;
 socktest -> magic = MAGIC_ALIVE ;
 TSContDataSet ( cont , socktest ) ;
 load ( TRANSFORM_APPEND_STRING ) ;
 TSHttpHookAdd ( TS_HTTP_READ_REQUEST_HDR_HOOK , cont ) ;
 TSHttpHookAdd ( TS_HTTP_READ_RESPONSE_HDR_HOOK , cont ) ;
 socktest -> os = synserver_create ( SYNSERVER_LISTEN_PORT ) ;
 synserver_start ( socktest -> os ) ;
 socktest -> browser1 = synclient_txn_create ( ) ;
 socktest -> browser2 = synclient_txn_create ( ) ;
 socktest -> browser3 = synclient_txn_create ( ) ;
 socktest -> browser4 = synclient_txn_create ( ) ;
 socktest -> request1 = generate_request ( 4 ) ;
 socktest -> request2 = generate_request ( 5 ) ;
 Debug ( UTDBG_TAG "_transform" , "Running Browser 1" ) ;
 synclient_txn_send_request ( socktest -> browser1 , socktest -> request1 ) ;
 TSContSchedule ( cont , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return ;
 }
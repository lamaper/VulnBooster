EXCLUSIVE_REGRESSION_TEST ( SDK_API_HttpHookAdd ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 TSCont cont = TSContCreate ( mytest_handler , TSMutexCreate ( ) ) ;
 SocketTest * socktest = ( SocketTest * ) TSmalloc ( sizeof ( SocketTest ) ) ;
 socktest -> regtest = test ;
 socktest -> pstatus = pstatus ;
 socktest -> hook_mask = 0 ;
 socktest -> reenable_mask = 0 ;
 socktest -> test_client_ip_get = false ;
 socktest -> test_client_incoming_port_get = false ;
 socktest -> test_client_req_get = false ;
 socktest -> test_client_resp_get = false ;
 socktest -> test_server_ip_get = false ;
 socktest -> test_server_req_get = false ;
 socktest -> test_server_resp_get = false ;
 socktest -> test_next_hop_ip_get = false ;
 socktest -> magic = MAGIC_ALIVE ;
 TSContDataSet ( cont , socktest ) ;
 TSHttpHookAdd ( TS_HTTP_TXN_START_HOOK , cont ) ;
 TSHttpHookAdd ( TS_HTTP_READ_REQUEST_HDR_HOOK , cont ) ;
 TSHttpHookAdd ( TS_HTTP_OS_DNS_HOOK , cont ) ;
 TSHttpHookAdd ( TS_HTTP_CACHE_LOOKUP_COMPLETE_HOOK , cont ) ;
 TSHttpHookAdd ( TS_HTTP_SEND_REQUEST_HDR_HOOK , cont ) ;
 TSHttpHookAdd ( TS_HTTP_READ_RESPONSE_HDR_HOOK , cont ) ;
 TSHttpHookAdd ( TS_HTTP_SEND_RESPONSE_HDR_HOOK , cont ) ;
 TSHttpHookAdd ( TS_HTTP_TXN_CLOSE_HOOK , cont ) ;
 socktest -> os = synserver_create ( SYNSERVER_LISTEN_PORT ) ;
 synserver_start ( socktest -> os ) ;
 socktest -> browser = synclient_txn_create ( ) ;
 char * request = generate_request ( HTTP_HOOK_TEST_REQUEST_ID ) ;
 synclient_txn_send_request ( socktest -> browser , request ) ;
 TSfree ( request ) ;
 if ( socktest -> browser -> status == REQUEST_INPROGRESS ) {
 TSContSchedule ( cont , 25 , TS_THREAD_POOL_DEFAULT ) ;
 }
 return ;
 }
static int mytest_handler ( TSCont contp , TSEvent event , void * data ) {
 SocketTest * test = ( SocketTest * ) TSContDataGet ( contp ) ;
 if ( test == nullptr ) {
 if ( ( event == TS_EVENT_IMMEDIATE ) || ( event == TS_EVENT_TIMEOUT ) ) {
 return 0 ;
 }
 TSHttpTxnReenable ( ( TSHttpTxn ) data , TS_EVENT_HTTP_CONTINUE ) ;
 return 0 ;
 }
 TSAssert ( test -> magic == MAGIC_ALIVE ) ;
 TSAssert ( test -> browser -> magic == MAGIC_ALIVE ) ;
 switch ( event ) {
 case TS_EVENT_HTTP_TXN_START : if ( test -> hook_mask == 0 ) {
 test -> hook_mask |= 1 ;
 }
 TSHttpTxnReenable ( ( TSHttpTxn ) data , TS_EVENT_HTTP_CONTINUE ) ;
 test -> reenable_mask |= 1 ;
 break ;
 case TS_EVENT_HTTP_READ_REQUEST_HDR : if ( test -> hook_mask == 1 ) {
 test -> hook_mask |= 2 ;
 }
 TSSkipRemappingSet ( ( TSHttpTxn ) data , 1 ) ;
 checkHttpTxnClientReqGet ( test , data ) ;
 TSHttpTxnReenable ( ( TSHttpTxn ) data , TS_EVENT_HTTP_CONTINUE ) ;
 test -> reenable_mask |= 2 ;
 break ;
 case TS_EVENT_HTTP_OS_DNS : if ( test -> hook_mask == 3 || test -> hook_mask == 7 ) {
 test -> hook_mask |= 8 ;
 }
 checkHttpTxnIncomingAddrGet ( test , data ) ;
 checkHttpTxnClientAddrGet ( test , data ) ;
 checkHttpTxnClientIPGet ( test , data ) ;
 checkHttpTxnServerIPGet ( test , data ) ;
 TSHttpTxnReenable ( ( TSHttpTxn ) data , TS_EVENT_HTTP_CONTINUE ) ;
 test -> reenable_mask |= 8 ;
 break ;
 case TS_EVENT_HTTP_CACHE_LOOKUP_COMPLETE : if ( test -> hook_mask == 3 || test -> hook_mask == 11 ) {
 test -> hook_mask |= 4 ;
 }
 TSHttpTxnReenable ( ( TSHttpTxn ) data , TS_EVENT_HTTP_CONTINUE ) ;
 test -> reenable_mask |= 4 ;
 break ;
 case TS_EVENT_HTTP_SEND_REQUEST_HDR : if ( test -> hook_mask == 15 ) {
 test -> hook_mask |= 16 ;
 }
 checkHttpTxnServerReqGet ( test , data ) ;
 checkHttpTxnNextHopIPGet ( test , data ) ;
 checkHttpTxnClientProtocolStackContains ( test , data ) ;
 checkHttpTxnClientProtocolStackGet ( test , data ) ;
 TSHttpTxnReenable ( ( TSHttpTxn ) data , TS_EVENT_HTTP_CONTINUE ) ;
 test -> reenable_mask |= 16 ;
 break ;
 case TS_EVENT_HTTP_READ_RESPONSE_HDR : if ( test -> hook_mask == 31 ) {
 test -> hook_mask |= 32 ;
 }
 checkHttpTxnServerRespGet ( test , data ) ;
 TSHttpTxnReenable ( ( TSHttpTxn ) data , TS_EVENT_HTTP_CONTINUE ) ;
 test -> reenable_mask |= 32 ;
 break ;
 case TS_EVENT_HTTP_SEND_RESPONSE_HDR : if ( test -> hook_mask == 63 ) {
 test -> hook_mask |= 64 ;
 }
 checkHttpTxnClientRespGet ( test , data ) ;
 TSHttpTxnReenable ( ( TSHttpTxn ) data , TS_EVENT_HTTP_CONTINUE ) ;
 test -> reenable_mask |= 64 ;
 break ;
 case TS_EVENT_HTTP_TXN_CLOSE : if ( test -> hook_mask == 127 ) {
 test -> hook_mask |= 128 ;
 }
 TSHttpTxnReenable ( ( TSHttpTxn ) data , TS_EVENT_HTTP_CONTINUE ) ;
 test -> reenable_mask |= 128 ;
 break ;
 case TS_EVENT_IMMEDIATE : case TS_EVENT_TIMEOUT : if ( test -> browser -> status == REQUEST_INPROGRESS ) {
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 }
 else {
 if ( ( test -> browser -> status == REQUEST_SUCCESS ) && ( test -> hook_mask == 255 ) ) {
 * ( test -> pstatus ) = REGRESSION_TEST_PASSED ;
 SDK_RPRINT ( test -> regtest , "TSHttpHookAdd" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 * ( test -> pstatus ) = REGRESSION_TEST_FAILED ;
 SDK_RPRINT ( test -> regtest , "TSHttpHookAdd" , "TestCase1" , TC_FAIL , "Hooks not called or request failure. Hook mask = %d\n %s" , test -> hook_mask , test -> browser -> response ) ;
 }
 if ( test -> reenable_mask == 255 ) {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnReenable" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 * ( test -> pstatus ) = REGRESSION_TEST_FAILED ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnReenable" , "TestCase1" , TC_FAIL , "Txn not re-enabled properly" ) ;
 }
 if ( ( test -> test_client_ip_get != true ) || ( test -> test_client_incoming_port_get != true ) || ( test -> test_client_remote_port_get != true ) || ( test -> test_client_req_get != true ) || ( test -> test_client_resp_get != true ) || ( test -> test_server_ip_get != true ) || ( test -> test_server_req_get != true ) || ( test -> test_server_resp_get != true ) || ( test -> test_next_hop_ip_get != true ) ) {
 * ( test -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 synclient_txn_delete ( test -> browser ) ;
 synserver_delete ( test -> os ) ;
 test -> os = nullptr ;
 test -> magic = MAGIC_DEAD ;
 TSfree ( test ) ;
 TSContDataSet ( contp , nullptr ) ;
 }
 break ;
 default : * ( test -> pstatus ) = REGRESSION_TEST_FAILED ;
 SDK_RPRINT ( test -> regtest , "TSHttpHookAdd" , "TestCase1" , TC_FAIL , "Unexpected event %d" , event ) ;
 break ;
 }
 return TS_EVENT_IMMEDIATE ;
 }
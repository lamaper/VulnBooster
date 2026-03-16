static int parent_proxy_handler ( TSCont contp , TSEvent event , void * edata ) {
 ParentTest * ptest = nullptr ;
 CHECK_SPURIOUS_EVENT ( contp , event , edata ) ;
 ptest = ( ParentTest * ) TSContDataGet ( contp ) ;
 ink_release_assert ( ptest ) ;
 TSHttpTxn txnp = ( TSHttpTxn ) edata ;
 switch ( event ) {
 case TS_EVENT_HTTP_READ_REQUEST_HDR : rprintf ( ptest -> regtest , "setting synserver parent proxy to %s:%d\n" , "127.0.0.1" , SYNSERVER_LISTEN_PORT ) ;
 TSHttpTxnParentProxySet ( txnp , "127.0.0.1" , SYNSERVER_LISTEN_PORT ) ;
 TSHttpTxnHookAdd ( txnp , TS_HTTP_SEND_RESPONSE_HDR_HOOK , contp ) ;
 TSHttpTxnHookAdd ( txnp , TS_HTTP_TXN_CLOSE_HOOK , contp ) ;
 TSSkipRemappingSet ( txnp , 1 ) ;
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 break ;
 case TS_EVENT_TIMEOUT : if ( * ( ptest -> pstatus ) == REGRESSION_TEST_INPROGRESS ) {
 if ( ptest -> configured ) {
 rprintf ( ptest -> regtest , "waiting for response\n" ) ;
 TSContSchedule ( contp , 100 , TS_THREAD_POOL_DEFAULT ) ;
 break ;
 }
 if ( ! ptest -> parent_routing_enabled ( ) ) {
 rprintf ( ptest -> regtest , "waiting for configuration\n" ) ;
 TSContSchedule ( contp , 100 , TS_THREAD_POOL_DEFAULT ) ;
 break ;
 }
 char * request = generate_request ( 11 ) ;
 synclient_txn_send_request ( ptest -> browser , request ) ;
 TSfree ( request ) ;
 ptest -> configured = true ;
 }
 else {
 RecSetRecordInt ( "proxy.config.http.parent_proxy_routing_enable" , ptest -> parent_proxy_routing_enable , REC_SOURCE_EXPLICIT ) ;
 TSContDataSet ( contp , nullptr ) ;
 delete ptest ;
 }
 break ;
 case TS_EVENT_HTTP_TXN_CLOSE : if ( * ( ptest -> pstatus ) == REGRESSION_TEST_INPROGRESS ) {
 * ( ptest -> pstatus ) = REGRESSION_TEST_FAILED ;
 SDK_RPRINT ( ptest -> regtest , "TSHttpTxnParentProxySet" , ptest -> testcase , TC_FAIL , "Failed on txn close" ) ;
 }
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 break ;
 default : {
 int status = ptest -> handler ( contp , event , edata ) ;
 if ( status != REGRESSION_TEST_INPROGRESS ) {
 int * pstatus = ptest -> pstatus ;
 RecSetRecordInt ( "proxy.config.http.parent_proxy_routing_enable" , ptest -> parent_proxy_routing_enable , REC_SOURCE_EXPLICIT ) ;
 TSContDataSet ( contp , nullptr ) ;
 delete ptest ;
 * pstatus = status ;
 }
 }
 }
 return TS_EVENT_NONE ;
 }
static int parent_proxy_success ( TSCont contp , TSEvent event , void * edata ) {
 ParentTest * ptest = ( ParentTest * ) TSContDataGet ( contp ) ;
 TSHttpTxn txnp = ( TSHttpTxn ) edata ;
 int expected ;
 int received ;
 int status ;
 switch ( event ) {
 case TS_EVENT_HTTP_SEND_RESPONSE_HDR : expected = get_request_id ( txnp ) ;
 received = get_response_id ( txnp ) ;
 if ( expected != received ) {
 status = REGRESSION_TEST_FAILED ;
 SDK_RPRINT ( ptest -> regtest , "TSHttpTxnParentProxySet" , "TestCase" , TC_FAIL , "Expected response ID %d, received %d" , expected , received ) ;
 }
 else {
 status = REGRESSION_TEST_PASSED ;
 SDK_RPRINT ( ptest -> regtest , "TSHttpTxnParentProxySet" , "TestCase" , TC_PASS , "Received expected response ID %d" , expected ) ;
 }
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 return status ;
 default : SDK_RPRINT ( ptest -> regtest , "TSHttpTxnParentProxySet" , ptest -> testcase , TC_FAIL , "Unexpected event %d" , event ) ;
 return REGRESSION_TEST_FAILED ;
 }
 }
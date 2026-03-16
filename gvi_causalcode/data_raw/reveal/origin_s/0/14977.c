static int parent_proxy_fail ( TSCont contp , TSEvent event , void * edata ) {
 ParentTest * ptest = ( ParentTest * ) TSContDataGet ( contp ) ;
 TSHttpTxn txnp = ( TSHttpTxn ) edata ;
 TSMBuffer mbuf ;
 TSMLoc hdr ;
 TSHttpStatus expected = TS_HTTP_STATUS_BAD_GATEWAY ;
 TSHttpStatus received ;
 int status ;
 switch ( event ) {
 case TS_EVENT_HTTP_SEND_RESPONSE_HDR : ink_release_assert ( TSHttpTxnClientRespGet ( txnp , & mbuf , & hdr ) == TS_SUCCESS ) ;
 received = TSHttpHdrStatusGet ( mbuf , hdr ) ;
 if ( expected != received ) {
 status = REGRESSION_TEST_FAILED ;
 SDK_RPRINT ( ptest -> regtest , "TSHttpTxnParentProxySet" , "TestCase" , TC_FAIL , "Expected response status %d, received %d" , expected , received ) ;
 }
 else {
 status = REGRESSION_TEST_PASSED ;
 SDK_RPRINT ( ptest -> regtest , "TSHttpTxnParentProxySet" , "TestCase" , TC_PASS , "Received expected response status %d" , expected ) ;
 }
 TSHandleMLocRelease ( mbuf , TS_NULL_MLOC , hdr ) ;
 return status ;
 default : SDK_RPRINT ( ptest -> regtest , "TSHttpTxnParentProxySet" , ptest -> testcase , TC_FAIL , "Unexpected event %d" , event ) ;
 return REGRESSION_TEST_FAILED ;
 }
 }
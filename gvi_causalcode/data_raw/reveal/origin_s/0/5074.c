static int checkHttpTxnServerReqGet ( SocketTest * test , void * data ) {
 TSMBuffer bufp ;
 TSMLoc mloc ;
 TSHttpTxn txnp = ( TSHttpTxn ) data ;
 if ( TSHttpTxnServerReqGet ( txnp , & bufp , & mloc ) != TS_SUCCESS ) {
 test -> test_server_req_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnServerReqGet" , "TestCase1" , TC_FAIL , "Unable to get handle to server request" ) ;
 return TS_EVENT_CONTINUE ;
 }
 if ( ( bufp == reinterpret_cast < TSMBuffer > ( & ( ( HttpSM * ) txnp ) -> t_state . hdr_info . server_request ) ) && ( mloc == reinterpret_cast < TSMLoc > ( ( ( HttpSM * ) txnp ) -> t_state . hdr_info . server_request . m_http ) ) ) {
 test -> test_server_req_get = true ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnServerReqGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 test -> test_server_req_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnServerReqGet" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 return TS_EVENT_CONTINUE ;
 }
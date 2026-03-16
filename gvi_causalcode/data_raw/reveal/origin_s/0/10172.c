static int checkHttpTxnServerRespGet ( SocketTest * test , void * data ) {
 TSMBuffer bufp ;
 TSMLoc mloc ;
 TSHttpTxn txnp = ( TSHttpTxn ) data ;
 if ( TSHttpTxnServerRespGet ( txnp , & bufp , & mloc ) != TS_SUCCESS ) {
 test -> test_server_resp_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnServerRespGet" , "TestCase1" , TC_FAIL , "Unable to get handle to server response" ) ;
 return TS_EVENT_CONTINUE ;
 }
 if ( ( bufp == reinterpret_cast < TSMBuffer > ( & ( ( HttpSM * ) txnp ) -> t_state . hdr_info . server_response ) ) && ( mloc == reinterpret_cast < TSMLoc > ( ( ( HttpSM * ) txnp ) -> t_state . hdr_info . server_response . m_http ) ) ) {
 test -> test_server_resp_get = true ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnServerRespGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 test -> test_server_resp_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnServerRespGet" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 return TS_EVENT_CONTINUE ;
 }
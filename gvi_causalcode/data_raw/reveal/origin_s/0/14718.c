static int checkHttpTxnClientRespGet ( SocketTest * test , void * data ) {
 TSMBuffer bufp ;
 TSMLoc mloc ;
 TSHttpTxn txnp = ( TSHttpTxn ) data ;
 if ( TSHttpTxnClientRespGet ( txnp , & bufp , & mloc ) != TS_SUCCESS ) {
 test -> test_client_resp_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientRespGet" , "TestCase1" , TC_FAIL , "Unable to get handle to client response" ) ;
 return TS_EVENT_CONTINUE ;
 }
 if ( ( bufp == reinterpret_cast < TSMBuffer > ( & ( ( HttpSM * ) txnp ) -> t_state . hdr_info . client_response ) ) && ( mloc == reinterpret_cast < TSMLoc > ( ( ( HttpSM * ) txnp ) -> t_state . hdr_info . client_response . m_http ) ) ) {
 test -> test_client_resp_get = true ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientRespGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 test -> test_client_resp_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientRespGet" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 return TS_EVENT_CONTINUE ;
 }
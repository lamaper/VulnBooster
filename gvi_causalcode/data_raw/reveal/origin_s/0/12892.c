static int checkHttpTxnIncomingAddrGet ( SocketTest * test , void * data ) {
 uint16_t port ;
 HttpProxyPort * proxy_port = HttpProxyPort : : findHttp ( AF_INET ) ;
 TSHttpTxn txnp = ( TSHttpTxn ) data ;
 sockaddr const * ptr = TSHttpTxnIncomingAddrGet ( txnp ) ;
 if ( nullptr == proxy_port ) {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnIncomingPortGet" , "TestCase1" , TC_FAIL , "TSHttpTxnIncomingAddrGet failed to find configured HTTP port." ) ;
 test -> test_client_incoming_port_get = false ;
 return TS_EVENT_CONTINUE ;
 }
 if ( nullptr == ptr ) {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnIncomingPortGet" , "TestCase1" , TC_FAIL , "TSHttpTxnIncomingAddrGet returns 0 pointer" ) ;
 test -> test_client_incoming_port_get = false ;
 return TS_EVENT_CONTINUE ;
 }
 port = ats_ip_port_host_order ( ptr ) ;
 TSDebug ( UTDBG_TAG , "TS HTTP port = %x, Txn incoming client port %x" , proxy_port -> m_port , port ) ;
 if ( port == proxy_port -> m_port ) {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnIncomingAddrGet" , "TestCase1" , TC_PASS , "ok" ) ;
 test -> test_client_incoming_port_get = true ;
 }
 else {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnIncomingAddrGet" , "TestCase1" , TC_FAIL , "Value's Mismatch. From Function: %d Expected value: %d" , port , proxy_port -> m_port ) ;
 test -> test_client_incoming_port_get = false ;
 }
 return TS_EVENT_CONTINUE ;
 }
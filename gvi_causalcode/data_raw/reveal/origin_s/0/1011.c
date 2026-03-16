static int checkHttpTxnServerIPGet ( SocketTest * test , void * data ) {
 sockaddr const * ptr ;
 in_addr_t ip ;
 TSHttpTxn txnp = ( TSHttpTxn ) data ;
 in_addr_t actual_ip = htonl ( INADDR_LOOPBACK ) ;
 ptr = TSHttpTxnServerAddrGet ( txnp ) ;
 if ( nullptr == ptr || 0 == ( ip = ats_ip4_addr_cast ( ptr ) ) ) {
 test -> test_server_ip_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnServerIPGet" , "TestCase1" , TC_FAIL , "TSHttpTxnServerIPGet returns 0 %s" , ptr ? "address" : "pointer" ) ;
 return TS_EVENT_CONTINUE ;
 }
 if ( ip == actual_ip ) {
 test -> test_server_ip_get = true ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnServerIPGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 test -> test_server_ip_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnServerIPGet" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 return TS_EVENT_CONTINUE ;
 }
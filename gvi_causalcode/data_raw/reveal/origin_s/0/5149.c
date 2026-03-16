static int checkHttpTxnClientIPGet ( SocketTest * test , void * data ) {
 sockaddr const * ptr ;
 in_addr_t ip ;
 TSHttpTxn txnp = ( TSHttpTxn ) data ;
 in_addr_t actual_ip = htonl ( INADDR_LOOPBACK ) ;
 ptr = TSHttpTxnClientAddrGet ( txnp ) ;
 if ( ptr == nullptr || INADDR_ANY == ( ip = ats_ip4_addr_cast ( ptr ) ) ) {
 test -> test_client_ip_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientIPGet" , "TestCase1" , TC_FAIL , "TSHttpTxnClientIPGet returns 0 %s" , ptr ? "address" : "pointer" ) ;
 return TS_EVENT_CONTINUE ;
 }
 if ( ip == actual_ip ) {
 test -> test_client_ip_get = true ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientIPGet" , "TestCase1" , TC_PASS , "ok [%0.8x]" , ip ) ;
 }
 else {
 test -> test_client_ip_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientIPGet" , "TestCase1" , TC_FAIL , "Value's Mismatch [expected %.8x got %.8x]" , actual_ip , ip ) ;
 }
 return TS_EVENT_CONTINUE ;
 }
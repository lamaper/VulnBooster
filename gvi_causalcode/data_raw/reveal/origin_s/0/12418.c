static int checkHttpTxnNextHopIPGet ( SocketTest * test , void * data ) {
 TSHttpTxn txnp = ( TSHttpTxn ) data ;
 in_addr_t actual_ip = htonl ( INADDR_LOOPBACK ) ;
 sockaddr const * ptr ;
 in_addr_t nexthopip ;
 ptr = TSHttpTxnNextHopAddrGet ( txnp ) ;
 if ( ptr == nullptr || ( nexthopip = ats_ip4_addr_cast ( ptr ) ) == 0 ) {
 test -> test_next_hop_ip_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnNextHopIPGet" , "TestCase1" , TC_FAIL , "TSHttpTxnNextHopIPGet returns 0 %s" , ptr ? "address" : "pointer" ) ;
 return TS_EVENT_CONTINUE ;
 }
 if ( nexthopip == actual_ip ) {
 test -> test_next_hop_ip_get = true ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnNextHopIPGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 test -> test_next_hop_ip_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnNextHopIPGet" , "TestCase1" , TC_FAIL , "Value's Mismatch [expected %0.8x got %0.8x]" , actual_ip , nexthopip ) ;
 }
 return TS_EVENT_CONTINUE ;
 }
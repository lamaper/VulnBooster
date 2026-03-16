static int checkHttpTxnClientAddrGet ( SocketTest * test , void * data ) {
 uint16_t port ;
 uint16_t browser_port ;
 TSHttpTxn txnp = ( TSHttpTxn ) data ;
 sockaddr const * ptr = TSHttpTxnClientAddrGet ( txnp ) ;
 browser_port = test -> browser -> local_port ;
 if ( nullptr == ptr ) {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientClientAddrGet" , "TestCase2" , TC_FAIL , "TSHttpTxnClientAddrGet returned 0 pointer." ) ;
 test -> test_client_remote_port_get = false ;
 return TS_EVENT_CONTINUE ;
 }
 port = ats_ip_port_host_order ( ptr ) ;
 TSDebug ( UTDBG_TAG , "Browser port = %x, Txn remote port = %x" , browser_port , port ) ;
 if ( port == browser_port ) {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientAddrGet" , "TestCase1" , TC_PASS , "ok" ) ;
 test -> test_client_remote_port_get = true ;
 }
 else {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientAddrGet" , "TestCase1" , TC_FAIL , "Value's Mismatch. From Function: %d Expected Value: %d" , port , browser_port ) ;
 test -> test_client_remote_port_get = false ;
 }
 return TS_EVENT_CONTINUE ;
 }
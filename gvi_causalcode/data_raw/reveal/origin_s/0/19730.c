static int checkHttpTxnClientProtocolStackGet ( SocketTest * test , void * data ) {
 TSHttpTxn txnp = ( TSHttpTxn ) data ;
 const char * results [ 10 ] ;
 int count = 0 ;
 TSHttpTxnClientProtocolStackGet ( txnp , 10 , results , & count ) ;
 test -> test_client_protocol_stack_get = true ;
 if ( count != 3 ) {
 test -> test_client_protocol_stack_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientProtocolStackGet" , "TestCase1" , TC_FAIL , "count should be 3 is %d" , count ) ;
 }
 else if ( strcmp ( results [ 0 ] , "http/1.0" ) != 0 ) {
 test -> test_client_protocol_stack_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientProtocolStackGet" , "TestCase1" , TC_FAIL , "results[0] should be http/1.0 is %s" , results [ 0 ] ) ;
 }
 else if ( strcmp ( results [ 1 ] , "tcp" ) != 0 ) {
 test -> test_client_protocol_stack_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientProtocolStackGet" , "TestCase1" , TC_FAIL , "results[1] should be tcp is %s" , results [ 1 ] ) ;
 }
 else if ( strcmp ( results [ 2 ] , "ipv4" ) != 0 ) {
 test -> test_client_protocol_stack_get = false ;
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientProtocolStackGet" , "TestCase1" , TC_FAIL , "results[2] should be ipv4 is %s" , results [ 2 ] ) ;
 }
 else {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientProtocolStackGet" , "TestCase1" , TC_PASS , "ok stack_size=%d" , count ) ;
 }
 return TS_EVENT_CONTINUE ;
 }
static int checkHttpTxnClientProtocolStackContains ( SocketTest * test , void * data ) {
 TSHttpTxn txnp = ( TSHttpTxn ) data ;
 const char * ret_tag = TSHttpTxnClientProtocolStackContains ( txnp , "tcp" ) ;
 test -> test_client_protocol_stack_contains = true ;
 if ( ret_tag ) {
 const char * normalized_tag = TSNormalizedProtocolTag ( "tcp" ) ;
 if ( normalized_tag != ret_tag ) {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientProtocolStackContains" , "TestCase1" , TC_FAIL , "contains tcp, but normalized tag is wrong" ) ;
 }
 else {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientProtocolStackContains" , "TestCase1" , TC_PASS , "ok tcp" ) ;
 }
 }
 else {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientProtocolStackContains" , "TestCase1" , TC_FAIL , "missing tcp" ) ;
 test -> test_client_protocol_stack_contains = false ;
 }
 ret_tag = TSHttpTxnClientProtocolStackContains ( txnp , "udp" ) ;
 if ( ! ret_tag ) {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientProtocolStackContains" , "TestCase2" , TC_PASS , "ok no udp" ) ;
 }
 else {
 SDK_RPRINT ( test -> regtest , "TSHttpTxnClientProtocolStackContains" , "TestCase2" , TC_FAIL , "faulty udp report" ) ;
 test -> test_client_protocol_stack_contains = false ;
 }
 return TS_EVENT_CONTINUE ;
 }
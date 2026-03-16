const char * TSHttpTxnClientProtocolStackContains ( TSHttpTxn txnp , const char * tag ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 return sm -> client_protocol_contains ( ts : : StringView ( tag ) ) ;
 }
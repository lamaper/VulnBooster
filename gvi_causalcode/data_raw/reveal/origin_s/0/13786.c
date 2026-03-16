int64_t TSHttpTxnServerReqBodyBytesGet ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 return sm -> server_request_body_bytes ;
 }
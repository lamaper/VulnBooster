int TSHttpTxnServerReqHdrBytesGet ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 return sm -> server_request_hdr_bytes ;
 }
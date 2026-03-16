int TSHttpTxnClientRespHdrBytesGet ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 return sm -> client_response_hdr_bytes ;
 }
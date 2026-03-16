int TSHttpTxnClientReqIsServerStyle ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 return ( sm -> t_state . hdr_info . client_req_is_server_style ? 1 : 0 ) ;
 }
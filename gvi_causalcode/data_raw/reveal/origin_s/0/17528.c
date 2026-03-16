TSReturnCode TSHttpTxnServerAddrSet ( TSHttpTxn txnp , struct sockaddr const * addr ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = reinterpret_cast < HttpSM * > ( txnp ) ;
 if ( ats_ip_copy ( & sm -> t_state . server_info . dst_addr . sa , addr ) ) {
 sm -> t_state . api_server_addr_set = true ;
 return TS_SUCCESS ;
 }
 else {
 return TS_ERROR ;
 }
 }
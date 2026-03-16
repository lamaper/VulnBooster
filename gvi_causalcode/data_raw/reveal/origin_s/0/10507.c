TSReturnCode TSHttpTxnOutgoingAddrSet ( TSHttpTxn txnp , const struct sockaddr * addr ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 sm -> ua_session -> set_outbound_port ( ats_ip_port_host_order ( addr ) ) ;
 sm -> ua_session -> set_outbound_ip ( IpAddr ( addr ) ) ;
 return TS_ERROR ;
 }
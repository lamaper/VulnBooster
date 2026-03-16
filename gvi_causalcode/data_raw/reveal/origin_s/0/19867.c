void TSHttpTxnClientIncomingPortSet ( TSHttpTxn txnp , int port ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = reinterpret_cast < HttpSM * > ( txnp ) ;
 sm -> t_state . client_info . dst_addr . port ( ) = htons ( port ) ;
 }
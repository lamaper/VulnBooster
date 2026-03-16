TSReturnCode TSHttpTxnParentProxyGet ( TSHttpTxn txnp , const char * * hostname , int * port ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 * hostname = sm -> t_state . api_info . parent_proxy_name ;
 * port = sm -> t_state . api_info . parent_proxy_port ;
 return TS_SUCCESS ;
 }
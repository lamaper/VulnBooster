void TSHttpTxnParentProxySet ( TSHttpTxn txnp , const char * hostname , int port ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) hostname ) == TS_SUCCESS ) ;
 sdk_assert ( port > 0 ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 sm -> t_state . api_info . parent_proxy_name = sm -> t_state . arena . str_store ( hostname , strlen ( hostname ) ) ;
 sm -> t_state . api_info . parent_proxy_port = port ;
 }
void TSHttpTxnReqCacheableSet ( TSHttpTxn txnp , int flag ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 sm -> t_state . api_req_cacheable = ( flag != 0 ) ;
 }
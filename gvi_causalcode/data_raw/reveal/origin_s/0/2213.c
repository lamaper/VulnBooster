void TSHttpTxnTransformedRespCache ( TSHttpTxn txnp , int on ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 sm -> t_state . api_info . cache_transformed = ( on ? true : false ) ;
 }
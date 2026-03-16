TSReturnCode TSHttpTxnCachedRespTimeGet ( TSHttpTxn txnp , time_t * resp_time ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HTTPInfo * cached_obj = sm -> t_state . cache_info . object_read ;
 if ( cached_obj == nullptr || ! cached_obj -> valid ( ) ) {
 return TS_ERROR ;
 }
 * resp_time = cached_obj -> response_received_time_get ( ) ;
 return TS_SUCCESS ;
 }
TSReturnCode TSHttpTxnCacheLookupCountGet ( TSHttpTxn txnp , int * lookup_count ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) lookup_count ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 * lookup_count = sm -> t_state . cache_info . lookup_count ;
 return TS_SUCCESS ;
 }
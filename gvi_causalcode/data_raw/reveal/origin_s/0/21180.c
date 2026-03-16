TSReturnCode TSHttpTxnSecondUrlTryLock ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HttpTransact : : State * s = & ( sm -> t_state ) ;
 if ( ! s -> cache_info . original_url . valid ( ) ) {
 return TS_ERROR ;
 }
 sm -> add_cache_sm ( ) ;
 s -> api_lock_url = HttpTransact : : LOCK_URL_SECOND ;
 return TS_SUCCESS ;
 }
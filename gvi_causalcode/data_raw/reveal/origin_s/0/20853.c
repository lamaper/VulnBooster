uint64_t TSHttpTxnIdGet ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 return ( uint64_t ) sm -> sm_id ;
 }
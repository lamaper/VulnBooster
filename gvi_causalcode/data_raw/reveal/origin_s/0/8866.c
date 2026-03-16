void TSSkipRemappingSet ( TSHttpTxn txnp , int flag ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 sm -> t_state . api_skip_all_remapping = ( flag != 0 ) ;
 }
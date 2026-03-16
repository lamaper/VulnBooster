int TSHttpTxnDebugGet ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 return ( ( HttpSM * ) txnp ) -> debug_on ;
 }
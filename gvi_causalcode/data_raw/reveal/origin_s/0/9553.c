void TSHttpTxnDebugSet ( TSHttpTxn txnp , int on ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 ( ( HttpSM * ) txnp ) -> debug_on = on ;
 }
void TSHttpTxnActiveTimeoutSet ( TSHttpTxn txnp , int timeout ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpTransact : : State * s = & ( ( ( HttpSM * ) txnp ) -> t_state ) ;
 s -> api_txn_active_timeout_value = timeout ;
 }
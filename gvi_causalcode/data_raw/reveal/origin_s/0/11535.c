void TSHttpTxnNoActivityTimeoutSet ( TSHttpTxn txnp , int timeout ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpTransact : : State * s = & ( ( ( HttpSM * ) txnp ) -> t_state ) ;
 s -> api_txn_no_activity_timeout_value = timeout ;
 }
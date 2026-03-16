TSReturnCode TSHttpTxnShutDown ( TSHttpTxn txnp , TSEvent event ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 if ( event == TS_EVENT_HTTP_TXN_CLOSE ) {
 return TS_ERROR ;
 }
 HttpTransact : : State * s = & ( ( ( HttpSM * ) txnp ) -> t_state ) ;
 s -> api_http_sm_shutdown = true ;
 return TS_SUCCESS ;
 }
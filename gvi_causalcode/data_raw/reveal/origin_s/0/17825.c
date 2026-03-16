TSReturnCode TSHttpTxnServerRespNoStoreSet ( TSHttpTxn txnp , int flag ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpTransact : : State * s = & ( ( ( HttpSM * ) txnp ) -> t_state ) ;
 s -> api_server_response_no_store = ( flag != 0 ) ;
 return TS_SUCCESS ;
 }
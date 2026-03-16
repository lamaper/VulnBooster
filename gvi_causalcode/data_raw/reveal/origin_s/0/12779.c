int TSHttpTxnLookingUpTypeGet ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HttpTransact : : State * s = & ( sm -> t_state ) ;
 return ( int ) ( s -> current . request_to ) ;
 }
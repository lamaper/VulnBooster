int TSHttpTxnBackgroundFillStarted ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * s = ( HttpSM * ) txnp ;
 return ( s -> background_fill == BACKGROUND_FILL_STARTED ) ;
 }
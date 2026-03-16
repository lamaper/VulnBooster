TSReturnCode TSHttpTxnFollowRedirect ( TSHttpTxn txnp , int on ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 sm -> enable_redirection = ( on ? true : false ) ;
 return TS_SUCCESS ;
 }
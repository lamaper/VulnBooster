TSReturnCode TSHttpTxnAborted ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 switch ( sm -> t_state . squid_codes . log_code ) {
 case SQUID_LOG_ERR_CLIENT_ABORT : case SQUID_LOG_TCP_SWAPFAIL : return TS_SUCCESS ;
 default : break ;
 }
 if ( sm -> t_state . current . server && sm -> t_state . current . server -> abort == HttpTransact : : ABORTED ) {
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }
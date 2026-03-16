TSReturnCode TSHttpTxnCloseAfterResponse ( TSHttpTxn txnp , int should_close ) {
 if ( sdk_sanity_check_txn ( txnp ) != TS_SUCCESS ) {
 return TS_ERROR ;
 }
 HttpSM * sm = ( HttpSM * ) txnp ;
 if ( should_close ) {
 sm -> t_state . client_info . keep_alive = HTTP_NO_KEEPALIVE ;
 if ( sm -> ua_session ) {
 sm -> set_ua_half_close_flag ( ) ;
 }
 }
 else if ( sm -> t_state . client_info . keep_alive == HTTP_NO_KEEPALIVE ) {
 sm -> t_state . client_info . keep_alive = HTTP_KEEPALIVE ;
 }
 return TS_SUCCESS ;
 }
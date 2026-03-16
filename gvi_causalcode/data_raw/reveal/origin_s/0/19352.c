TSReturnCode TSHttpTxnPrivateSessionSet ( TSHttpTxn txnp , int private_session ) {
 if ( sdk_sanity_check_txn ( txnp ) != TS_SUCCESS ) {
 return TS_ERROR ;
 }
 HttpSM * sm = ( HttpSM * ) txnp ;
 if ( sm -> set_server_session_private ( private_session ) ) {
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }
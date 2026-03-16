TSReturnCode TSHttpTxnServerRespIgnore ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpTransact : : State * s = & ( ( ( HttpSM * ) txnp ) -> t_state ) ;
 HTTPInfo * cached_obj = s -> cache_info . object_read ;
 HTTPHdr * cached_resp ;
 if ( cached_obj == nullptr || ! cached_obj -> valid ( ) ) {
 return TS_ERROR ;
 }
 cached_resp = cached_obj -> response_get ( ) ;
 if ( cached_resp == nullptr || ! cached_resp -> valid ( ) ) {
 return TS_ERROR ;
 }
 s -> api_server_response_ignore = true ;
 return TS_SUCCESS ;
 }
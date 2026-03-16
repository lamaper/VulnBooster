TSReturnCode TSHttpTxnUpdateCachedObject ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HttpTransact : : State * s = & ( sm -> t_state ) ;
 HTTPInfo * cached_obj_store = & ( sm -> t_state . cache_info . object_store ) ;
 HTTPHdr * client_request = & ( sm -> t_state . hdr_info . client_request ) ;
 if ( ! cached_obj_store -> valid ( ) || ! cached_obj_store -> response_get ( ) ) {
 return TS_ERROR ;
 }
 if ( ! cached_obj_store -> request_get ( ) && ! client_request -> valid ( ) ) {
 return TS_ERROR ;
 }
 if ( s -> cache_info . write_lock_state == HttpTransact : : CACHE_WL_READ_RETRY ) {
 return TS_ERROR ;
 }
 s -> api_update_cached_object = HttpTransact : : UPDATE_CACHED_OBJECT_PREPARE ;
 return TS_SUCCESS ;
 }
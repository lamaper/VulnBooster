TSReturnCode TSHttpTxnCachedRespModifiableGet ( TSHttpTxn txnp , TSMBuffer * bufp , TSMLoc * obj ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) obj ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HttpTransact : : State * s = & ( sm -> t_state ) ;
 HTTPHdr * c_resp = nullptr ;
 HTTPInfo * cached_obj = sm -> t_state . cache_info . object_read ;
 HTTPInfo * cached_obj_store = & ( sm -> t_state . cache_info . object_store ) ;
 if ( ( ! cached_obj ) || ( ! cached_obj -> valid ( ) ) ) {
 return TS_ERROR ;
 }
 if ( ! cached_obj_store -> valid ( ) ) {
 cached_obj_store -> create ( ) ;
 }
 c_resp = cached_obj_store -> response_get ( ) ;
 if ( c_resp == nullptr || ! c_resp -> valid ( ) ) {
 cached_obj_store -> response_set ( cached_obj -> response_get ( ) ) ;
 }
 c_resp = cached_obj_store -> response_get ( ) ;
 s -> api_modifiable_cached_resp = true ;
 ink_assert ( c_resp != nullptr && c_resp -> valid ( ) ) ;
 * ( reinterpret_cast < HTTPHdr * * > ( bufp ) ) = c_resp ;
 * obj = reinterpret_cast < TSMLoc > ( c_resp -> m_http ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( * bufp ) == TS_SUCCESS ) ;
 return TS_SUCCESS ;
 }
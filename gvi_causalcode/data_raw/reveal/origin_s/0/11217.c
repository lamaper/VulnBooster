TSReturnCode TSHttpTxnNewCacheLookupDo ( TSHttpTxn txnp , TSMBuffer bufp , TSMLoc url_loc ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( url_loc ) == TS_SUCCESS ) ;
 URL new_url , * client_url , * l_url , * o_url ;
 INK_MD5 md51 , md52 ;
 new_url . m_heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 new_url . m_url_impl = ( URLImpl * ) url_loc ;
 if ( ! new_url . valid ( ) ) {
 return TS_ERROR ;
 }
 HttpSM * sm = ( HttpSM * ) txnp ;
 HttpTransact : : State * s = & ( sm -> t_state ) ;
 client_url = s -> hdr_info . client_request . url_get ( ) ;
 if ( ! ( client_url -> valid ( ) ) ) {
 return TS_ERROR ;
 }
 l_url = s -> cache_info . lookup_url ;
 if ( ! l_url || ! l_url -> valid ( ) ) {
 s -> cache_info . lookup_url_storage . create ( nullptr ) ;
 s -> cache_info . lookup_url = & ( s -> cache_info . lookup_url_storage ) ;
 l_url = s -> cache_info . lookup_url ;
 }
 else {
 l_url -> hash_get ( & md51 ) ;
 new_url . hash_get ( & md52 ) ;
 if ( md51 == md52 ) {
 return TS_ERROR ;
 }
 o_url = & ( s -> cache_info . original_url ) ;
 if ( ! o_url -> valid ( ) ) {
 o_url -> create ( nullptr ) ;
 o_url -> copy ( l_url ) ;
 }
 }
 l_url -> copy ( & new_url ) ;
 s -> transact_return_point = HttpTransact : : DecideCacheLookup ;
 s -> cache_info . action = HttpTransact : : CACHE_DO_LOOKUP ;
 sm -> add_cache_sm ( ) ;
 s -> api_cleanup_cache_read = true ;
 return TS_SUCCESS ;
 }
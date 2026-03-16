TSReturnCode TSCacheUrlSet ( TSHttpTxn txnp , const char * url , int length ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 Debug ( "cache_url" , "[TSCacheUrlSet]" ) ;
 if ( sm -> t_state . cache_info . lookup_url == nullptr ) {
 Debug ( "cache_url" , "[TSCacheUrlSet] changing the cache url to: %s" , url ) ;
 if ( length == - 1 ) {
 length = strlen ( url ) ;
 }
 sm -> t_state . cache_info . lookup_url_storage . create ( nullptr ) ;
 sm -> t_state . cache_info . lookup_url = & ( sm -> t_state . cache_info . lookup_url_storage ) ;
 sm -> t_state . cache_info . lookup_url -> parse ( url , length ) ;
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }
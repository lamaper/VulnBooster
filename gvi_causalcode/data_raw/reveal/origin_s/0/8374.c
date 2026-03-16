TSReturnCode TSHttpTxnCacheLookupStatusSet ( TSHttpTxn txnp , int cachelookup ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HttpTransact : : CacheLookupResult_t * sm_status = & ( sm -> t_state . cache_lookup_result ) ;
 if ( * sm_status == HttpTransact : : CACHE_LOOKUP_MISS && cachelookup != TS_CACHE_LOOKUP_MISS ) {
 return TS_ERROR ;
 }
 if ( cachelookup == TS_CACHE_LOOKUP_MISS && * sm_status != HttpTransact : : CACHE_LOOKUP_MISS ) {
 sm -> t_state . api_cleanup_cache_read = true ;
 ink_assert ( sm -> t_state . transact_return_point != nullptr ) ;
 sm -> t_state . transact_return_point = HttpTransact : : HandleCacheOpenRead ;
 }
 switch ( cachelookup ) {
 case TS_CACHE_LOOKUP_MISS : * sm_status = HttpTransact : : CACHE_LOOKUP_MISS ;
 break ;
 case TS_CACHE_LOOKUP_HIT_STALE : * sm_status = HttpTransact : : CACHE_LOOKUP_HIT_STALE ;
 break ;
 case TS_CACHE_LOOKUP_HIT_FRESH : * sm_status = HttpTransact : : CACHE_LOOKUP_HIT_FRESH ;
 break ;
 default : return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }
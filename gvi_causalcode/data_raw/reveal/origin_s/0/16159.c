TSReturnCode TSHttpTxnCacheLookupStatusGet ( TSHttpTxn txnp , int * lookup_status ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) lookup_status ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 switch ( sm -> t_state . cache_lookup_result ) {
 case HttpTransact : : CACHE_LOOKUP_MISS : case HttpTransact : : CACHE_LOOKUP_DOC_BUSY : * lookup_status = TS_CACHE_LOOKUP_MISS ;
 break ;
 case HttpTransact : : CACHE_LOOKUP_HIT_STALE : * lookup_status = TS_CACHE_LOOKUP_HIT_STALE ;
 break ;
 case HttpTransact : : CACHE_LOOKUP_HIT_WARNING : case HttpTransact : : CACHE_LOOKUP_HIT_FRESH : * lookup_status = TS_CACHE_LOOKUP_HIT_FRESH ;
 break ;
 case HttpTransact : : CACHE_LOOKUP_SKIPPED : * lookup_status = TS_CACHE_LOOKUP_SKIPPED ;
 break ;
 case HttpTransact : : CACHE_LOOKUP_NONE : default : return TS_ERROR ;
 }
 ;
 return TS_SUCCESS ;
 }
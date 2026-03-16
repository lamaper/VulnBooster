char * TSFetchRespGet ( TSHttpTxn txnp , int * length ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) length ) == TS_SUCCESS ) ;
 FetchSM * fetch_sm = ( FetchSM * ) txnp ;
 return fetch_sm -> resp_get ( length ) ;
 }
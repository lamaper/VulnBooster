char * TSHttpTxnEffectiveUrlStringGet ( TSHttpTxn txnp , int * length ) {
 sdk_assert ( TS_SUCCESS == sdk_sanity_check_txn ( txnp ) ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) length ) == TS_SUCCESS ) ;
 HttpSM * sm = reinterpret_cast < HttpSM * > ( txnp ) ;
 return sm -> t_state . hdr_info . client_request . url_string_get ( nullptr , length ) ;
 }
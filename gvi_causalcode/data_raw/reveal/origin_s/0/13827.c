const char * TSHttpTxnRedirectUrlGet ( TSHttpTxn txnp , int * url_len_ptr ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 * url_len_ptr = sm -> redirect_url_len ;
 return sm -> redirect_url ;
 }
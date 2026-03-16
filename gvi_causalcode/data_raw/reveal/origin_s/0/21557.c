void TSHttpTxnRedirectUrlSet ( TSHttpTxn txnp , const char * url , const int url_len ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) url ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 if ( sm -> redirect_url != nullptr ) {
 ats_free ( sm -> redirect_url ) ;
 sm -> redirect_url = nullptr ;
 sm -> redirect_url_len = 0 ;
 }
 sm -> redirect_url = ( char * ) url ;
 sm -> redirect_url_len = url_len ;
 sm -> enable_redirection = true ;
 }
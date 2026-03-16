void TSRedirectUrlSet ( TSHttpTxn txnp , const char * url , const int url_len ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) url ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 if ( sm -> redirect_url != nullptr ) {
 ats_free ( sm -> redirect_url ) ;
 sm -> redirect_url = nullptr ;
 sm -> redirect_url_len = 0 ;
 }
 sm -> redirect_url = ( char * ) ats_malloc ( url_len + 1 ) ;
 ink_strlcpy ( sm -> redirect_url , url , url_len + 1 ) ;
 sm -> redirect_url_len = url_len ;
 if ( sm -> enable_redirection == false ) {
 sm -> enable_redirection = true ;
 sm -> redirection_tries = sm -> t_state . txn_conf -> number_of_redirections ;
 }
 }
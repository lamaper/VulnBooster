TSReturnCode TSHttpTxnRedirectRequest ( TSHttpTxn txnp , TSMBuffer bufp , TSMLoc url_loc ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( url_loc ) == TS_SUCCESS ) ;
 URL u , * o_url , * r_url , * client_url ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HttpTransact : : State * s = & ( sm -> t_state ) ;
 u . m_heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 u . m_url_impl = ( URLImpl * ) url_loc ;
 if ( ! u . valid ( ) ) {
 return TS_ERROR ;
 }
 client_url = s -> hdr_info . client_request . url_get ( ) ;
 if ( ! ( client_url -> valid ( ) ) ) {
 return TS_ERROR ;
 }
 s -> redirect_info . redirect_in_process = true ;
 o_url = & ( s -> redirect_info . original_url ) ;
 if ( ! o_url -> valid ( ) ) {
 o_url -> create ( nullptr ) ;
 o_url -> copy ( client_url ) ;
 }
 client_url -> copy ( & u ) ;
 r_url = & ( s -> redirect_info . redirect_url ) ;
 if ( ! r_url -> valid ( ) ) {
 r_url -> create ( nullptr ) ;
 }
 r_url -> copy ( & u ) ;
 s -> hdr_info . server_request . destroy ( ) ;
 s -> request_sent_time = 0 ;
 s -> response_received_time = 0 ;
 s -> cache_info . write_lock_state = HttpTransact : : CACHE_WL_INIT ;
 s -> next_action = HttpTransact : : SM_ACTION_REDIRECT_READ ;
 return TS_SUCCESS ;
 }
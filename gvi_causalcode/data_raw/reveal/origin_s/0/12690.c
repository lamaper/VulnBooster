TSReturnCode TSHttpTxnPristineUrlGet ( TSHttpTxn txnp , TSMBuffer * bufp , TSMLoc * url_loc ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) url_loc ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HTTPHdr * hptr = & ( sm -> t_state . hdr_info . client_request ) ;
 if ( hptr -> valid ( ) ) {
 * ( reinterpret_cast < HTTPHdr * * > ( bufp ) ) = hptr ;
 * url_loc = ( TSMLoc ) sm -> t_state . unmapped_url . m_url_impl ;
 if ( sdk_sanity_check_mbuffer ( * bufp ) == TS_SUCCESS ) {
 if ( * url_loc == nullptr ) {
 * url_loc = ( TSMLoc ) hptr -> m_http -> u . req . m_url_impl ;
 }
 if ( * url_loc ) {
 return TS_SUCCESS ;
 }
 }
 }
 return TS_ERROR ;
 }
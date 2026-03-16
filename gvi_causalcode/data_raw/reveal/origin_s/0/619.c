TSReturnCode TSHttpTxnClientReqGet ( TSHttpTxn txnp , TSMBuffer * bufp , TSMLoc * obj ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) obj ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HTTPHdr * hptr = & ( sm -> t_state . hdr_info . client_request ) ;
 if ( hptr -> valid ( ) ) {
 * ( reinterpret_cast < HTTPHdr * * > ( bufp ) ) = hptr ;
 * obj = reinterpret_cast < TSMLoc > ( hptr -> m_http ) ;
 if ( sdk_sanity_check_mbuffer ( * bufp ) == TS_SUCCESS ) {
 hptr -> mark_target_dirty ( ) ;
 return TS_SUCCESS ;
 ;
 }
 }
 return TS_ERROR ;
 }
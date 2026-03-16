TSReturnCode TSHttpTxnTransformRespGet ( TSHttpTxn txnp , TSMBuffer * bufp , TSMLoc * obj ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HTTPHdr * hptr = & ( sm -> t_state . hdr_info . transform_response ) ;
 if ( hptr -> valid ( ) ) {
 * ( reinterpret_cast < HTTPHdr * * > ( bufp ) ) = hptr ;
 * obj = reinterpret_cast < TSMLoc > ( hptr -> m_http ) ;
 return sdk_sanity_check_mbuffer ( * bufp ) ;
 }
 return TS_ERROR ;
 }
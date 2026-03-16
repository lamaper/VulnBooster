TSReturnCode TSFetchPageRespGet ( TSHttpTxn txnp , TSMBuffer * bufp , TSMLoc * obj ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) obj ) == TS_SUCCESS ) ;
 HTTPHdr * hptr = ( HTTPHdr * ) txnp ;
 if ( hptr -> valid ( ) ) {
 * ( reinterpret_cast < HTTPHdr * * > ( bufp ) ) = hptr ;
 * obj = reinterpret_cast < TSMLoc > ( hptr -> m_http ) ;
 return sdk_sanity_check_mbuffer ( * bufp ) ;
 }
 return TS_ERROR ;
 }
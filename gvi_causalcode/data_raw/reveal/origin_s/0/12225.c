TSParseResult TSHttpHdrParseResp ( TSHttpParser parser , TSMBuffer bufp , TSMLoc obj , const char * * start , const char * end ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) start ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) * start ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) end ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_PARSE_ERROR ;
 }
 HTTPHdr h ;
 SET_HTTP_HDR ( h , bufp , obj ) ;
 ink_assert ( h . m_http -> m_type == HDR_HEAP_OBJ_HTTP_HEADER ) ;
 TSHttpHdrTypeSet ( bufp , obj , TS_HTTP_TYPE_RESPONSE ) ;
 return ( TSParseResult ) h . parse_resp ( ( HTTPParser * ) parser , start , end , false ) ;
 }
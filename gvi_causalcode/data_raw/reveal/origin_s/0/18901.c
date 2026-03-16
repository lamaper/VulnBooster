int TSHttpHdrLengthGet ( TSMBuffer bufp , TSMLoc obj ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ;
 HTTPHdr h ;
 SET_HTTP_HDR ( h , bufp , obj ) ;
 ink_assert ( h . m_http -> m_type == HDR_HEAP_OBJ_HTTP_HEADER ) ;
 return h . length_get ( ) ;
 }
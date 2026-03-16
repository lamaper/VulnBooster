TSReturnCode TSHttpHdrVersionSet ( TSMBuffer bufp , TSMLoc obj , int ver ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 HTTPHdr h ;
 HTTPVersion version ( ver ) ;
 SET_HTTP_HDR ( h , bufp , obj ) ;
 ink_assert ( h . m_http -> m_type == HDR_HEAP_OBJ_HTTP_HEADER ) ;
 h . version_set ( version ) ;
 return TS_SUCCESS ;
 }
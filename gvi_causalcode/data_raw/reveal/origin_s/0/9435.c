int TSHttpHdrVersionGet ( TSMBuffer bufp , TSMLoc obj ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ;
 HTTPHdr h ;
 SET_HTTP_HDR ( h , bufp , obj ) ;
 HTTPVersion ver = h . version_get ( ) ;
 return ver . m_version ;
 }
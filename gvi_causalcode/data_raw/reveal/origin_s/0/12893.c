TSHttpStatus TSHttpHdrStatusGet ( TSMBuffer bufp , TSMLoc obj ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ;
 HTTPHdr h ;
 SET_HTTP_HDR ( h , bufp , obj ) ;
 return ( TSHttpStatus ) h . status_get ( ) ;
 }
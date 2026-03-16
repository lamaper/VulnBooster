const char * TSHttpHdrReasonGet ( TSMBuffer bufp , TSMLoc obj , int * length ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) length ) == TS_SUCCESS ) ;
 HTTPHdr h ;
 SET_HTTP_HDR ( h , bufp , obj ) ;
 return h . reason_get ( length ) ;
 }
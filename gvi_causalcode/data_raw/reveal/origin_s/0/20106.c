TSReturnCode TSHttpHdrReasonSet ( TSMBuffer bufp , TSMLoc obj , const char * value , int length ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) value ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 HTTPHdr h ;
 SET_HTTP_HDR ( h , bufp , obj ) ;
 if ( length < 0 ) {
 length = strlen ( value ) ;
 }
 h . reason_set ( value , length ) ;
 return TS_SUCCESS ;
 }
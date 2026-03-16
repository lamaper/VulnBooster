TSReturnCode TSHttpHdrTypeSet ( TSMBuffer bufp , TSMLoc obj , TSHttpType type ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ;
 sdk_assert ( ( type >= TS_HTTP_TYPE_UNKNOWN ) && ( type <= TS_HTTP_TYPE_RESPONSE ) ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 HTTPHdr h ;
 SET_HTTP_HDR ( h , bufp , obj ) ;
 ink_assert ( h . m_http -> m_type == HDR_HEAP_OBJ_HTTP_HEADER ) ;
 if ( h . m_http -> m_polarity == HTTP_TYPE_UNKNOWN ) {
 if ( type == ( TSHttpType ) HTTP_TYPE_REQUEST ) {
 h . m_http -> u . req . m_url_impl = url_create ( h . m_heap ) ;
 h . m_http -> m_polarity = ( HTTPType ) type ;
 }
 else if ( type == ( TSHttpType ) HTTP_TYPE_RESPONSE ) {
 h . m_http -> m_polarity = ( HTTPType ) type ;
 }
 }
 return TS_SUCCESS ;
 }
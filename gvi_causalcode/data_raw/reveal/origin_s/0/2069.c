TSReturnCode TSHttpHdrUrlSet ( TSMBuffer bufp , TSMLoc obj , TSMLoc url ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( url ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 HdrHeap * heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 HTTPHdrImpl * hh = ( HTTPHdrImpl * ) obj ;
 if ( hh -> m_type != HDR_HEAP_OBJ_HTTP_HEADER ) {
 return TS_ERROR ;
 }
 URLImpl * url_impl = ( URLImpl * ) url ;
 http_hdr_url_set ( heap , hh , url_impl ) ;
 return TS_SUCCESS ;
 }
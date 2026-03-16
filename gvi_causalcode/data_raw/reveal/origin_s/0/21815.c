TSReturnCode TSUrlCreate ( TSMBuffer bufp , TSMLoc * locp ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( locp ) == TS_SUCCESS ) ;
 if ( isWriteable ( bufp ) ) {
 HdrHeap * heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 * locp = ( TSMLoc ) url_create ( heap ) ;
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }
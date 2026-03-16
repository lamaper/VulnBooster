TSMLoc TSHttpHdrCreate ( TSMBuffer bufp ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 HTTPHdr h ;
 h . m_heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 h . create ( HTTP_TYPE_UNKNOWN ) ;
 return ( TSMLoc ) ( h . m_http ) ;
 }
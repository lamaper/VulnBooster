TSMBuffer TSMBufferCreate ( void ) {
 TSMBuffer bufp ;
 HdrHeapSDKHandle * new_heap = new HdrHeapSDKHandle ;
 new_heap -> m_heap = new_HdrHeap ( ) ;
 bufp = ( TSMBuffer ) new_heap ;
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 return bufp ;
 }
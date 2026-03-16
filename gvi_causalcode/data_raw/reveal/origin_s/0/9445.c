TSReturnCode TSMBufferDestroy ( TSMBuffer bufp ) {
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 HdrHeapSDKHandle * sdk_heap = ( HdrHeapSDKHandle * ) bufp ;
 sdk_heap -> m_heap -> destroy ( ) ;
 delete sdk_heap ;
 return TS_SUCCESS ;
 }
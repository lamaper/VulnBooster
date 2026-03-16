TSReturnCode sdk_sanity_check_mbuffer ( TSMBuffer bufp ) {
 HdrHeapSDKHandle * handle = ( HdrHeapSDKHandle * ) bufp ;
 if ( ( handle == nullptr ) || ( handle -> m_heap == nullptr ) || ( handle -> m_heap -> m_magic != HDR_BUF_MAGIC_ALIVE ) ) {
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }
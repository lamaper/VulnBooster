TSReturnCode TSMimeHdrCreate ( TSMBuffer bufp , TSMLoc * locp ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) locp ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 * locp = reinterpret_cast < TSMLoc > ( mime_hdr_create ( ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ) ) ;
 return TS_SUCCESS ;
 }
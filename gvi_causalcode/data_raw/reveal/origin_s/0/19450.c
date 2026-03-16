TSReturnCode TSUrlClone ( TSMBuffer dest_bufp , TSMBuffer src_bufp , TSMLoc src_url , TSMLoc * locp ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( src_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( dest_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( src_url ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( locp ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( dest_bufp ) ) {
 return TS_ERROR ;
 }
 HdrHeap * s_heap , * d_heap ;
 URLImpl * s_url , * d_url ;
 s_heap = ( ( HdrHeapSDKHandle * ) src_bufp ) -> m_heap ;
 d_heap = ( ( HdrHeapSDKHandle * ) dest_bufp ) -> m_heap ;
 s_url = ( URLImpl * ) src_url ;
 d_url = url_copy ( s_url , s_heap , d_heap , ( s_heap != d_heap ) ) ;
 * locp = ( TSMLoc ) d_url ;
 return TS_SUCCESS ;
 }
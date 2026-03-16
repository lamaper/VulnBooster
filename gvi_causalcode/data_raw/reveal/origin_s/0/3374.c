TSReturnCode TSUrlCopy ( TSMBuffer dest_bufp , TSMLoc dest_obj , TSMBuffer src_bufp , TSMLoc src_obj ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( src_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( dest_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( src_obj ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( dest_obj ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( dest_bufp ) ) {
 return TS_ERROR ;
 }
 HdrHeap * s_heap , * d_heap ;
 URLImpl * s_url , * d_url ;
 s_heap = ( ( HdrHeapSDKHandle * ) src_bufp ) -> m_heap ;
 d_heap = ( ( HdrHeapSDKHandle * ) dest_bufp ) -> m_heap ;
 s_url = ( URLImpl * ) src_obj ;
 d_url = ( URLImpl * ) dest_obj ;
 url_copy_onto ( s_url , s_heap , d_url , d_heap , ( s_heap != d_heap ) ) ;
 return TS_SUCCESS ;
 }
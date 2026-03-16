TSReturnCode TSHttpHdrClone ( TSMBuffer dest_bufp , TSMBuffer src_bufp , TSMLoc src_hdr , TSMLoc * locp ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( dest_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( src_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( src_hdr ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( dest_bufp ) ) {
 return TS_ERROR ;
 }
 HdrHeap * s_heap , * d_heap ;
 HTTPHdrImpl * s_hh , * d_hh ;
 s_heap = ( ( HdrHeapSDKHandle * ) src_bufp ) -> m_heap ;
 d_heap = ( ( HdrHeapSDKHandle * ) dest_bufp ) -> m_heap ;
 s_hh = ( HTTPHdrImpl * ) src_hdr ;
 if ( s_hh -> m_type != HDR_HEAP_OBJ_HTTP_HEADER ) {
 return TS_ERROR ;
 }
 d_hh = http_hdr_clone ( s_hh , s_heap , d_heap ) ;
 * locp = ( TSMLoc ) d_hh ;
 return TS_SUCCESS ;
 }
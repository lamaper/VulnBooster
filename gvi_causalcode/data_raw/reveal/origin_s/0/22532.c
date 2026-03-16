TSReturnCode TSHttpHdrCopy ( TSMBuffer dest_bufp , TSMLoc dest_obj , TSMBuffer src_bufp , TSMLoc src_obj ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( src_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( dest_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( dest_obj ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( src_obj ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( dest_bufp ) ) {
 return TS_ERROR ;
 }
 bool inherit_strs ;
 HdrHeap * s_heap , * d_heap ;
 HTTPHdrImpl * s_hh , * d_hh ;
 s_heap = ( ( HdrHeapSDKHandle * ) src_bufp ) -> m_heap ;
 d_heap = ( ( HdrHeapSDKHandle * ) dest_bufp ) -> m_heap ;
 s_hh = ( HTTPHdrImpl * ) src_obj ;
 d_hh = ( HTTPHdrImpl * ) dest_obj ;
 if ( ( s_hh -> m_type != HDR_HEAP_OBJ_HTTP_HEADER ) || ( d_hh -> m_type != HDR_HEAP_OBJ_HTTP_HEADER ) ) {
 return TS_ERROR ;
 }
 inherit_strs = ( s_heap != d_heap ? true : false ) ;
 TSHttpHdrTypeSet ( dest_bufp , dest_obj , ( TSHttpType ) ( s_hh -> m_polarity ) ) ;
 http_hdr_copy_onto ( s_hh , s_heap , d_hh , d_heap , inherit_strs ) ;
 return TS_SUCCESS ;
 }
TSReturnCode TSMimeHdrClone ( TSMBuffer dest_bufp , TSMBuffer src_bufp , TSMLoc src_hdr , TSMLoc * locp ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( dest_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( src_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mime_hdr_handle ( src_hdr ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( src_hdr ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) locp ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( dest_bufp ) ) {
 return TS_ERROR ;
 }
 HdrHeap * s_heap , * d_heap ;
 MIMEHdrImpl * s_mh , * d_mh ;
 s_heap = ( ( HdrHeapSDKHandle * ) src_bufp ) -> m_heap ;
 d_heap = ( ( HdrHeapSDKHandle * ) dest_bufp ) -> m_heap ;
 s_mh = _hdr_mloc_to_mime_hdr_impl ( src_hdr ) ;
 d_mh = mime_hdr_clone ( s_mh , s_heap , d_heap , ( s_heap != d_heap ) ) ;
 * locp = ( TSMLoc ) d_mh ;
 return TS_SUCCESS ;
 }
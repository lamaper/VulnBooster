TSReturnCode TSMimeHdrCopy ( TSMBuffer dest_bufp , TSMLoc dest_obj , TSMBuffer src_bufp , TSMLoc src_obj ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( src_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( dest_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( src_obj ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( src_obj ) == TS_SUCCESS ) ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( dest_obj ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( dest_obj ) == TS_SUCCESS ) ) ;
 if ( ! isWriteable ( dest_bufp ) ) {
 return TS_ERROR ;
 }
 HdrHeap * s_heap , * d_heap ;
 MIMEHdrImpl * s_mh , * d_mh ;
 s_heap = ( ( HdrHeapSDKHandle * ) src_bufp ) -> m_heap ;
 d_heap = ( ( HdrHeapSDKHandle * ) dest_bufp ) -> m_heap ;
 s_mh = _hdr_mloc_to_mime_hdr_impl ( src_obj ) ;
 d_mh = _hdr_mloc_to_mime_hdr_impl ( dest_obj ) ;
 mime_hdr_fields_clear ( d_heap , d_mh ) ;
 mime_hdr_copy_onto ( s_mh , s_heap , d_mh , d_heap , ( s_heap != d_heap ) ) ;
 return TS_SUCCESS ;
 }
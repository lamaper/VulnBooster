TSReturnCode TSMimeHdrFieldCopyValues ( TSMBuffer dest_bufp , TSMLoc dest_hdr , TSMLoc dest_field , TSMBuffer src_bufp , TSMLoc src_hdr , TSMLoc src_field ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( src_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( dest_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( src_hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( src_hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( dest_hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( dest_hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( src_field , src_hdr ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( dest_field , dest_hdr ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( dest_bufp ) ) {
 return TS_ERROR ;
 }
 MIMEFieldSDKHandle * s_handle = ( MIMEFieldSDKHandle * ) src_field ;
 MIMEFieldSDKHandle * d_handle = ( MIMEFieldSDKHandle * ) dest_field ;
 HdrHeap * d_heap = ( ( HdrHeapSDKHandle * ) dest_bufp ) -> m_heap ;
 MIMEField * s_field , * d_field ;
 s_field = s_handle -> field_ptr ;
 d_field = d_handle -> field_ptr ;
 mime_field_value_set ( d_heap , d_handle -> mh , d_field , s_field -> m_ptr_value , s_field -> m_len_value , true ) ;
 return TS_SUCCESS ;
 }
TSReturnCode TSMimeHdrFieldCopy ( TSMBuffer dest_bufp , TSMLoc dest_hdr , TSMLoc dest_field , TSMBuffer src_bufp , TSMLoc src_hdr , TSMLoc src_field ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( src_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( dest_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( src_hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( src_hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( dest_hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( dest_hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( src_field , src_hdr ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( dest_field , dest_hdr ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( dest_bufp ) ) {
 return TS_ERROR ;
 }
 bool dest_attached ;
 MIMEFieldSDKHandle * s_handle = ( MIMEFieldSDKHandle * ) src_field ;
 MIMEFieldSDKHandle * d_handle = ( MIMEFieldSDKHandle * ) dest_field ;
 HdrHeap * d_heap = ( ( HdrHeapSDKHandle * ) dest_bufp ) -> m_heap ;
 dest_attached = ( d_handle -> mh && d_handle -> field_ptr -> is_live ( ) ) ;
 if ( dest_attached ) {
 mime_hdr_field_detach ( d_handle -> mh , d_handle -> field_ptr , false ) ;
 }
 mime_field_name_value_set ( d_heap , d_handle -> mh , d_handle -> field_ptr , s_handle -> field_ptr -> m_wks_idx , s_handle -> field_ptr -> m_ptr_name , s_handle -> field_ptr -> m_len_name , s_handle -> field_ptr -> m_ptr_value , s_handle -> field_ptr -> m_len_value , 0 , 0 , true ) ;
 if ( dest_attached ) {
 mime_hdr_field_attach ( d_handle -> mh , d_handle -> field_ptr , 1 , nullptr ) ;
 }
 return TS_SUCCESS ;
 }
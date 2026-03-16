TSReturnCode TSMimeHdrFieldValueDelete ( TSMBuffer bufp , TSMLoc hdr , TSMLoc field , int idx ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field , hdr ) == TS_SUCCESS ) ;
 sdk_assert ( idx >= 0 ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 MIMEFieldSDKHandle * handle = ( MIMEFieldSDKHandle * ) field ;
 HdrHeap * heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 mime_field_value_delete_comma_val ( heap , handle -> mh , handle -> field_ptr , idx ) ;
 return TS_SUCCESS ;
 }
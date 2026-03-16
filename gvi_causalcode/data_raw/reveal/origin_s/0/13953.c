TSReturnCode TSMimeHdrFieldValuesClear ( TSMBuffer bufp , TSMLoc hdr , TSMLoc field ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field , hdr ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 MIMEFieldSDKHandle * handle = ( MIMEFieldSDKHandle * ) field ;
 HdrHeap * heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 mime_field_value_set ( heap , handle -> mh , handle -> field_ptr , nullptr , 0 , true ) ;
 return TS_SUCCESS ;
 }
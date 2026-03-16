TSReturnCode TSMimeHdrFieldNameSet ( TSMBuffer bufp , TSMLoc hdr , TSMLoc field , const char * name , int length ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field , hdr ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) name ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 if ( length == - 1 ) {
 length = strlen ( name ) ;
 }
 MIMEFieldSDKHandle * handle = ( MIMEFieldSDKHandle * ) field ;
 HdrHeap * heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 int attached = ( handle -> mh && handle -> field_ptr -> is_live ( ) ) ;
 if ( attached ) {
 mime_hdr_field_detach ( handle -> mh , handle -> field_ptr , false ) ;
 }
 handle -> field_ptr -> name_set ( heap , handle -> mh , name , length ) ;
 if ( attached ) {
 mime_hdr_field_attach ( handle -> mh , handle -> field_ptr , 1 , nullptr ) ;
 }
 return TS_SUCCESS ;
 }
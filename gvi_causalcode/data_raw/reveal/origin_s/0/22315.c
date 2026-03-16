const char * TSMimeHdrFieldNameGet ( TSMBuffer bufp , TSMLoc hdr , TSMLoc field , int * length ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field , hdr ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) length ) == TS_SUCCESS ) ;
 MIMEFieldSDKHandle * handle = ( MIMEFieldSDKHandle * ) field ;
 return mime_field_name_get ( handle -> field_ptr , length ) ;
 }
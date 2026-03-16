TSReturnCode TSMimeHdrFieldValueDateInsert ( TSMBuffer bufp , TSMLoc hdr , TSMLoc field , time_t value ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field , hdr ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 if ( TSMimeHdrFieldValuesClear ( bufp , hdr , field ) == TS_ERROR ) {
 return TS_ERROR ;
 }
 char tmp [ 33 ] ;
 int len = mime_format_date ( tmp , value ) ;
 ( void ) TSMimeFieldValueSet ( bufp , field , - 1 , tmp , len ) ;
 return TS_SUCCESS ;
 }
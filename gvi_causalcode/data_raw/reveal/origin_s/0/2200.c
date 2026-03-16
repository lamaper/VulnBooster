int TSMimeHdrFieldValueIntGet ( TSMBuffer bufp , TSMLoc hdr , TSMLoc field , int idx ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field , hdr ) == TS_SUCCESS ) ;
 int value_len ;
 const char * value_str = TSMimeFieldValueGet ( bufp , field , idx , & value_len ) ;
 if ( value_str == nullptr ) {
 return 0 ;
 }
 return mime_parse_int ( value_str , value_str + value_len ) ;
 }
int TSMimeHdrFieldValuesCount ( TSMBuffer bufp , TSMLoc hdr , TSMLoc field ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field , hdr ) == TS_SUCCESS ) ;
 MIMEFieldSDKHandle * handle = ( MIMEFieldSDKHandle * ) field ;
 return mime_field_value_get_comma_val_count ( handle -> field_ptr ) ;
 }
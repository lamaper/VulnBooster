const char * TSMimeHdrFieldValueStringGet ( TSMBuffer bufp , TSMLoc hdr , TSMLoc field , int idx , int * value_len_ptr ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field , hdr ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) value_len_ptr ) == TS_SUCCESS ) ;
 return TSMimeFieldValueGet ( bufp , field , idx , value_len_ptr ) ;
 }
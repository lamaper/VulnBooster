TSReturnCode TSMimeHdrFieldValueInt64Set ( TSMBuffer bufp , TSMLoc hdr , TSMLoc field , int idx , int64_t value ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field , hdr ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 char tmp [ 20 ] ;
 int len = mime_format_int64 ( tmp , value , sizeof ( tmp ) ) ;
 TSMimeFieldValueSet ( bufp , field , idx , tmp , len ) ;
 return TS_SUCCESS ;
 }
TSReturnCode TSMimeHdrFieldValueIntInsert ( TSMBuffer bufp , TSMLoc hdr , TSMLoc field , int idx , int value ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field , hdr ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 char tmp [ 16 ] ;
 int len = mime_format_int ( tmp , value , sizeof ( tmp ) ) ;
 TSMimeFieldValueInsert ( bufp , field , tmp , len , idx ) ;
 return TS_SUCCESS ;
 }
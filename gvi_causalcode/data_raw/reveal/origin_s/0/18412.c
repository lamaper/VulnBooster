TSMLoc TSMimeHdrFieldNext ( TSMBuffer bufp , TSMLoc hdr , TSMLoc field ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field , hdr ) == TS_SUCCESS ) ;
 MIMEFieldSDKHandle * handle = ( MIMEFieldSDKHandle * ) field ;
 if ( handle -> mh == nullptr ) {
 return TS_NULL_MLOC ;
 }
 int slotnum = mime_hdr_field_slotnum ( handle -> mh , handle -> field_ptr ) ;
 if ( slotnum == - 1 ) {
 return TS_NULL_MLOC ;
 }
 while ( true ) {
 ++ slotnum ;
 MIMEField * f = mime_hdr_field_get_slotnum ( handle -> mh , slotnum ) ;
 if ( f == nullptr ) {
 return TS_NULL_MLOC ;
 }
 if ( f -> is_live ( ) ) {
 MIMEFieldSDKHandle * h = sdk_alloc_field_handle ( bufp , handle -> mh ) ;
 h -> field_ptr = f ;
 return reinterpret_cast < TSMLoc > ( h ) ;
 }
 }
 return TS_NULL_MLOC ;
 }
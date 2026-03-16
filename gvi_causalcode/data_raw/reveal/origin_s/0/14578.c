TSMLoc TSMimeHdrFieldNextDup ( TSMBuffer bufp , TSMLoc hdr , TSMLoc field ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field , hdr ) == TS_SUCCESS ) ;
 MIMEHdrImpl * mh = _hdr_mloc_to_mime_hdr_impl ( hdr ) ;
 MIMEFieldSDKHandle * field_handle = ( MIMEFieldSDKHandle * ) field ;
 MIMEField * next = field_handle -> field_ptr -> m_next_dup ;
 if ( next == nullptr ) {
 return TS_NULL_MLOC ;
 }
 MIMEFieldSDKHandle * next_handle = sdk_alloc_field_handle ( bufp , mh ) ;
 next_handle -> field_ptr = next ;
 return ( TSMLoc ) next_handle ;
 }
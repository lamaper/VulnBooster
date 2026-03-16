TSMLoc TSMimeHdrFieldGet ( TSMBuffer bufp , TSMLoc hdr_obj , int idx ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( hdr_obj ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( hdr_obj ) == TS_SUCCESS ) ) ;
 sdk_assert ( idx >= 0 ) ;
 MIMEHdrImpl * mh = _hdr_mloc_to_mime_hdr_impl ( hdr_obj ) ;
 MIMEField * f = mime_hdr_field_get ( mh , idx ) ;
 if ( f == nullptr ) {
 return TS_NULL_MLOC ;
 }
 MIMEFieldSDKHandle * h = sdk_alloc_field_handle ( bufp , mh ) ;
 h -> field_ptr = f ;
 return reinterpret_cast < TSMLoc > ( h ) ;
 }
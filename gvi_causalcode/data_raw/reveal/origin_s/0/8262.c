int TSMimeHdrLengthGet ( TSMBuffer bufp , TSMLoc obj ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( obj ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ) ;
 MIMEHdrImpl * mh = _hdr_mloc_to_mime_hdr_impl ( obj ) ;
 return mime_hdr_length_get ( mh ) ;
 }
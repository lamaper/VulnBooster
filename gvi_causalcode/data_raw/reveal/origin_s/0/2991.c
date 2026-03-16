TSReturnCode TSMimeHdrFieldClone ( TSMBuffer dest_bufp , TSMLoc dest_hdr , TSMBuffer src_bufp , TSMLoc src_hdr , TSMLoc src_field , TSMLoc * locp ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( dest_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( src_bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( dest_hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( dest_hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( src_hdr ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( src_hdr ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( src_field , src_hdr ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) locp ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( dest_bufp ) ) {
 return TS_ERROR ;
 }
 if ( TSMimeHdrFieldCreate ( dest_bufp , dest_hdr , locp ) == TS_SUCCESS ) {
 TSMimeHdrFieldCopy ( dest_bufp , dest_hdr , * locp , src_bufp , src_hdr , src_field ) ;
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }
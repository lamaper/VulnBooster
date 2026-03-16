TSReturnCode TSMimeHdrDestroy ( TSMBuffer bufp , TSMLoc obj ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( obj ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 MIMEHdrImpl * mh = _hdr_mloc_to_mime_hdr_impl ( obj ) ;
 mime_hdr_destroy ( ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap , mh ) ;
 return TS_SUCCESS ;
 }
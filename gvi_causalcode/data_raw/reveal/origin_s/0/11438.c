TSReturnCode TSMimeHdrFieldDestroy ( TSMBuffer bufp , TSMLoc mh_mloc , TSMLoc field_mloc ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( mh_mloc ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( mh_mloc ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field_mloc , mh_mloc ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 MIMEFieldSDKHandle * field_handle = ( MIMEFieldSDKHandle * ) field_mloc ;
 if ( field_handle -> mh == nullptr ) {
 ink_release_assert ( ! "Failed MH" ) ;
 }
 else {
 MIMEHdrImpl * mh = _hdr_mloc_to_mime_hdr_impl ( mh_mloc ) ;
 HdrHeap * heap = ( HdrHeap * ) ( ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ) ;
 ink_assert ( mh == field_handle -> mh ) ;
 if ( sdk_sanity_check_field_handle ( field_mloc , mh_mloc ) != TS_SUCCESS ) {
 return TS_ERROR ;
 }
 mime_hdr_field_delete ( heap , mh , field_handle -> field_ptr , false ) ;
 }
 return TS_SUCCESS ;
 }
TSReturnCode TSMimeHdrFieldAppend ( TSMBuffer bufp , TSMLoc mh_mloc , TSMLoc field_mloc ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( mh_mloc ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( mh_mloc ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field_mloc ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 MIMEField * mh_field ;
 MIMEHdrImpl * mh = _hdr_mloc_to_mime_hdr_impl ( mh_mloc ) ;
 MIMEFieldSDKHandle * field_handle = ( MIMEFieldSDKHandle * ) field_mloc ;
 if ( field_handle -> mh == nullptr ) {
 HdrHeap * heap = ( HdrHeap * ) ( ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ) ;
 mh_field = mime_field_create ( heap , mh ) ;
 memcpy ( mh_field , field_handle -> field_ptr , sizeof ( MIMEField ) ) ;
 field_handle -> mh = mh ;
 field_handle -> field_ptr = mh_field ;
 }
 ink_assert ( field_handle -> mh == mh ) ;
 ink_assert ( field_handle -> field_ptr -> m_ptr_name ) ;
 mime_hdr_field_attach ( mh , field_handle -> field_ptr , 1 , nullptr ) ;
 return TS_SUCCESS ;
 }
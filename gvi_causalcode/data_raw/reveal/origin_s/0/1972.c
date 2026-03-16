TSReturnCode sdk_sanity_check_field_handle ( TSMLoc field , TSMLoc parent_hdr = nullptr ) {
 if ( field == TS_NULL_MLOC ) {
 return TS_ERROR ;
 }
 MIMEFieldSDKHandle * field_handle = ( MIMEFieldSDKHandle * ) field ;
 if ( field_handle -> m_type != HDR_HEAP_OBJ_FIELD_SDK_HANDLE ) {
 return TS_ERROR ;
 }
 if ( parent_hdr != nullptr ) {
 MIMEHdrImpl * mh = _hdr_mloc_to_mime_hdr_impl ( parent_hdr ) ;
 if ( field_handle -> mh != mh ) {
 return TS_ERROR ;
 }
 }
 return TS_SUCCESS ;
 }
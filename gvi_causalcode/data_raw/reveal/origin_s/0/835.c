TSReturnCode sdk_sanity_check_mime_hdr_handle ( TSMLoc field ) {
 if ( field == TS_NULL_MLOC ) {
 return TS_ERROR ;
 }
 MIMEFieldSDKHandle * field_handle = ( MIMEFieldSDKHandle * ) field ;
 if ( field_handle -> m_type != HDR_HEAP_OBJ_MIME_HEADER ) {
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }
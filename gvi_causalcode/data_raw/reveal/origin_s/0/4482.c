TSReturnCode sdk_sanity_check_http_hdr_handle ( TSMLoc field ) {
 if ( field == TS_NULL_MLOC ) {
 return TS_ERROR ;
 }
 HTTPHdrImpl * field_handle = ( HTTPHdrImpl * ) field ;
 if ( field_handle -> m_type != HDR_HEAP_OBJ_HTTP_HEADER ) {
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }
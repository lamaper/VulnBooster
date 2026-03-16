TSReturnCode TSHandleMLocRelease ( TSMBuffer bufp , TSMLoc parent , TSMLoc mloc ) {
 MIMEFieldSDKHandle * field_handle ;
 HdrHeapObjImpl * obj = ( HdrHeapObjImpl * ) mloc ;
 if ( mloc == TS_NULL_MLOC ) {
 return TS_SUCCESS ;
 }
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 switch ( obj -> m_type ) {
 case HDR_HEAP_OBJ_URL : case HDR_HEAP_OBJ_HTTP_HEADER : case HDR_HEAP_OBJ_MIME_HEADER : return TS_SUCCESS ;
 case HDR_HEAP_OBJ_FIELD_SDK_HANDLE : field_handle = ( MIMEFieldSDKHandle * ) obj ;
 if ( sdk_sanity_check_field_handle ( mloc , parent ) != TS_SUCCESS ) {
 return TS_ERROR ;
 }
 sdk_free_field_handle ( bufp , field_handle ) ;
 return TS_SUCCESS ;
 default : ink_release_assert ( ! "invalid mloc" ) ;
 return TS_ERROR ;
 }
 }
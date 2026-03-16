TSReturnCode TSUrlFtpTypeSet ( TSMBuffer bufp , TSMLoc obj , int type ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( obj ) == TS_SUCCESS ) ;
 if ( ( type == 0 || type == 'A' || type == 'E' || type == 'I' || type == 'a' || type == 'i' || type == 'e' ) && isWriteable ( bufp ) ) {
 URL u ;
 u . m_heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 u . m_url_impl = ( URLImpl * ) obj ;
 u . type_set ( type ) ;
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }
TSReturnCode TSUrlPortSet ( TSMBuffer bufp , TSMLoc obj , int port ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( obj ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) || ( port < 0 ) ) {
 return TS_ERROR ;
 }
 URL u ;
 u . m_heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 u . m_url_impl = ( URLImpl * ) obj ;
 u . port_set ( port ) ;
 return TS_SUCCESS ;
 }
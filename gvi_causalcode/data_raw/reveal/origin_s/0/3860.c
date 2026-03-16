TSParseResult TSUrlParse ( TSMBuffer bufp , TSMLoc obj , const char * * start , const char * end ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( obj ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) start ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) * start ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) end ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_PARSE_ERROR ;
 }
 URL u ;
 u . m_heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 u . m_url_impl = ( URLImpl * ) obj ;
 url_clear ( u . m_url_impl ) ;
 return ( TSParseResult ) u . parse ( start , end ) ;
 }
static TSReturnCode URLPartSet ( TSMBuffer bufp , TSMLoc obj , const char * value , int length , URLPartSetF url_f ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( obj ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_ERROR ;
 }
 URL u ;
 u . m_heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 u . m_url_impl = ( URLImpl * ) obj ;
 if ( ! value ) {
 length = 0 ;
 }
 else if ( length < 0 ) {
 length = strlen ( value ) ;
 }
 ( u . * url_f ) ( value , length ) ;
 return TS_SUCCESS ;
 }
TSReturnCode TSHttpHdrUrlGet ( TSMBuffer bufp , TSMLoc obj , TSMLoc * locp ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ;
 HTTPHdrImpl * hh = ( HTTPHdrImpl * ) obj ;
 if ( hh -> m_polarity != HTTP_TYPE_REQUEST ) {
 return TS_ERROR ;
 }
 * locp = ( ( TSMLoc ) hh -> u . req . m_url_impl ) ;
 return TS_SUCCESS ;
 }
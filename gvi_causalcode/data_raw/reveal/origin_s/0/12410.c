int TSUrlLengthGet ( TSMBuffer bufp , TSMLoc obj ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( obj ) == TS_SUCCESS ) ;
 URLImpl * url_impl = ( URLImpl * ) obj ;
 return url_length_get ( url_impl ) ;
 }
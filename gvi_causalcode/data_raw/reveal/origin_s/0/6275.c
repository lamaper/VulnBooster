char * TSUrlStringGet ( TSMBuffer bufp , TSMLoc obj , int * length ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( obj ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) length ) == TS_SUCCESS ) ;
 URLImpl * url_impl = ( URLImpl * ) obj ;
 return url_string_get ( url_impl , nullptr , length , nullptr ) ;
 }
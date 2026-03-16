TSReturnCode TSUrlPercentEncode ( TSMBuffer bufp , TSMLoc obj , char * dst , size_t dst_size , size_t * length , const unsigned char * map ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( obj ) == TS_SUCCESS ) ;
 char * url ;
 int url_len ;
 TSReturnCode ret ;
 URLImpl * url_impl = ( URLImpl * ) obj ;
 url = url_string_get ( url_impl , nullptr , & url_len , nullptr ) ;
 ret = TSStringPercentEncode ( url , url_len , dst , dst_size , length , map ) ;
 ats_free ( url ) ;
 return ret ;
 }
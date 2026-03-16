static bool use_http_1_1plus ( const struct Curl_easy * data , const struct connectdata * conn ) {
 if ( ( data -> state . httpversion == 10 ) || ( conn -> httpversion == 10 ) ) return FALSE ;
 if ( ( data -> set . httpversion == CURL_HTTP_VERSION_1_0 ) && ( conn -> httpversion <= 10 ) ) return FALSE ;
 return ( ( data -> set . httpversion == CURL_HTTP_VERSION_NONE ) || ( data -> set . httpversion >= CURL_HTTP_VERSION_1_1 ) ) ;
 }
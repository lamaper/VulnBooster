static int evhttp_is_connection_close ( int flags , struct evkeyvalq * headers ) {
 if ( flags & EVHTTP_PROXY_REQUEST ) {
 const char * connection = evhttp_find_header ( headers , "Proxy-Connection" ) ;
 return ( connection == NULL || strcasecmp ( connection , "keep-alive" ) != 0 ) ;
 }
 else {
 const char * connection = evhttp_find_header ( headers , "Connection" ) ;
 return ( connection != NULL && strcasecmp ( connection , "close" ) == 0 ) ;
 }
 }
static int evhttp_is_connection_keepalive ( struct evkeyvalq * headers ) {
 const char * connection = evhttp_find_header ( headers , "Connection" ) ;
 return ( connection != NULL && strncasecmp ( connection , "keep-alive" , 10 ) == 0 ) ;
 }
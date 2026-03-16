int evhttp_del_cb ( struct evhttp * http , const char * uri ) {
 struct evhttp_cb * http_cb ;
 TAILQ_FOREACH ( http_cb , & http -> callbacks , next ) {
 if ( strcmp ( http_cb -> what , uri ) == 0 ) break ;
 }
 if ( http_cb == NULL ) return ( - 1 ) ;
 TAILQ_REMOVE ( & http -> callbacks , http_cb , next ) ;
 free ( http_cb -> what ) ;
 free ( http_cb ) ;
 return ( 0 ) ;
 }
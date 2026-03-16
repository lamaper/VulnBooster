static struct evhttp * evhttp_new_object ( void ) {
 struct evhttp * http = NULL ;
 if ( ( http = calloc ( 1 , sizeof ( struct evhttp ) ) ) == NULL ) {
 event_warn ( "%s: calloc" , __func__ ) ;
 return ( NULL ) ;
 }
 http -> timeout = - 1 ;
 TAILQ_INIT ( & http -> sockets ) ;
 TAILQ_INIT ( & http -> callbacks ) ;
 TAILQ_INIT ( & http -> connections ) ;
 return ( http ) ;
 }
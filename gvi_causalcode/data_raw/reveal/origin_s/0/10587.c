int evhttp_accept_socket ( struct evhttp * http , int fd ) {
 struct evhttp_bound_socket * bound ;
 struct event * ev ;
 int res ;
 bound = malloc ( sizeof ( struct evhttp_bound_socket ) ) ;
 if ( bound == NULL ) return ( - 1 ) ;
 ev = & bound -> bind_ev ;
 event_set ( ev , fd , EV_READ | EV_PERSIST , accept_socket , http ) ;
 EVHTTP_BASE_SET ( http , ev ) ;
 res = event_add ( ev , NULL ) ;
 if ( res == - 1 ) {
 free ( bound ) ;
 return ( - 1 ) ;
 }
 TAILQ_INSERT_TAIL ( & http -> sockets , bound , next ) ;
 return ( 0 ) ;
 }
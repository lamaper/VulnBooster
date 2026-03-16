void evhttp_free ( struct evhttp * http ) {
 struct evhttp_cb * http_cb ;
 struct evhttp_connection * evcon ;
 struct evhttp_bound_socket * bound ;
 int fd ;
 while ( ( bound = TAILQ_FIRST ( & http -> sockets ) ) != NULL ) {
 TAILQ_REMOVE ( & http -> sockets , bound , next ) ;
 fd = bound -> bind_ev . ev_fd ;
 event_del ( & bound -> bind_ev ) ;
 EVUTIL_CLOSESOCKET ( fd ) ;
 free ( bound ) ;
 }
 while ( ( evcon = TAILQ_FIRST ( & http -> connections ) ) != NULL ) {
 evhttp_connection_free ( evcon ) ;
 }
 while ( ( http_cb = TAILQ_FIRST ( & http -> callbacks ) ) != NULL ) {
 TAILQ_REMOVE ( & http -> callbacks , http_cb , next ) ;
 free ( http_cb -> what ) ;
 free ( http_cb ) ;
 }
 free ( http ) ;
 }
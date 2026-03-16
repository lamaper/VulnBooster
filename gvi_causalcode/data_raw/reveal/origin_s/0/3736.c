int evhttp_bind_socket ( struct evhttp * http , const char * address , u_short port ) {
 int fd ;
 int res ;
 if ( ( fd = bind_socket ( address , port , 1 ) ) == - 1 ) return ( - 1 ) ;
 if ( listen ( fd , 128 ) == - 1 ) {
 event_warn ( "%s: listen" , __func__ ) ;
 EVUTIL_CLOSESOCKET ( fd ) ;
 return ( - 1 ) ;
 }
 res = evhttp_accept_socket ( http , fd ) ;
 if ( res != - 1 ) event_debug ( ( "Bound to port %d - Awaiting connections ... " , port ) ) ;
 return ( res ) ;
 }
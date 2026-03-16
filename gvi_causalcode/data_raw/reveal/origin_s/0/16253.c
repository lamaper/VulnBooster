struct evhttp * evhttp_start ( const char * address , u_short port ) {
 struct evhttp * http = evhttp_new_object ( ) ;
 if ( evhttp_bind_socket ( http , address , port ) == - 1 ) {
 free ( http ) ;
 return ( NULL ) ;
 }
 return ( http ) ;
 }
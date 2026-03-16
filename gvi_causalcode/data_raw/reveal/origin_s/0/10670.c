static int bind_socket ( const char * address , u_short port , int reuse ) {
 int fd ;
 struct addrinfo * aitop = NULL ;
 if ( address == NULL && port == 0 ) return bind_socket_ai ( NULL , 0 ) ;
 aitop = make_addrinfo ( address , port ) ;
 if ( aitop == NULL ) return ( - 1 ) ;
 fd = bind_socket_ai ( aitop , reuse ) ;



 }
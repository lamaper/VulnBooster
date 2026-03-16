static int socket_connect ( int fd , const char * address , unsigned short port ) {
 struct addrinfo * ai = make_addrinfo ( address , port ) ;
 int res = - 1 ;
 if ( ai == NULL ) {
 event_debug ( ( "%s: make_addrinfo: \"%s:%d\"" , __func__ , address , port ) ) ;
 return ( - 1 ) ;
 }
 if ( connect ( fd , ai -> ai_addr , ai -> ai_addrlen ) == - 1 ) {

 if ( tmp_error != WSAEWOULDBLOCK && tmp_error != WSAEINVAL && tmp_error != WSAEINPROGRESS ) {
 goto out ;
 }

 goto out ;
 }

 res = 0 ;
 out : # ifdef HAVE_GETADDRINFO freeaddrinfo ( ai ) ;


 }
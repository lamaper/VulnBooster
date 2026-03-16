static int bind_socket_ai ( struct addrinfo * ai , int reuse ) {
 int fd , on = 1 , r ;
 int serrno ;
 fd = socket ( AF_INET , SOCK_STREAM , 0 ) ;
 if ( fd == - 1 ) {
 event_warn ( "socket" ) ;
 return ( - 1 ) ;
 }
 if ( evutil_make_socket_nonblocking ( fd ) < 0 ) goto out ;

 event_warn ( "fcntl(F_SETFD)" ) ;
 goto out ;
 }

 if ( reuse ) {
 setsockopt ( fd , SOL_SOCKET , SO_REUSEADDR , ( void * ) & on , sizeof ( on ) ) ;
 }
 if ( ai != NULL ) {
 r = bind ( fd , ai -> ai_addr , ai -> ai_addrlen ) ;
 if ( r == - 1 ) goto out ;
 }
 return ( fd ) ;
 out : serrno = EVUTIL_SOCKET_ERROR ( ) ;
 EVUTIL_CLOSESOCKET ( fd ) ;
 EVUTIL_SET_SOCKET_ERROR ( serrno ) ;
 return ( - 1 ) ;
 }
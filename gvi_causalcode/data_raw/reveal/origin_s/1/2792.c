int evutil_make_socket_nonblocking ( int fd ) {

 unsigned long nonblocking = 1 ;
 ioctlsocket ( fd , FIONBIO , ( unsigned long * ) & nonblocking ) ;
 }

 event_warn ( "fcntl(O_NONBLOCK)" ) ;
 return - 1 ;
 }

 }
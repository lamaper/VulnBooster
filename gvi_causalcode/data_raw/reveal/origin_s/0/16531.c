static void accept_socket ( int fd , short what , void * arg ) {
 struct evhttp * http = arg ;
 struct sockaddr_storage ss ;
 socklen_t addrlen = sizeof ( ss ) ;
 int nfd ;
 if ( ( nfd = accept ( fd , ( struct sockaddr * ) & ss , & addrlen ) ) == - 1 ) {
 if ( errno != EAGAIN && errno != EINTR ) event_warn ( "%s: bad accept" , __func__ ) ;
 return ;
 }
 if ( evutil_make_socket_nonblocking ( nfd ) < 0 ) return ;
 evhttp_get_request ( http , nfd , ( struct sockaddr * ) & ss , addrlen ) ;
 }
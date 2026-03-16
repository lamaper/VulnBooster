int evutil_socketpair ( int family , int type , int protocol , int fd [ 2 ] ) {


 int connector = - 1 ;
 int acceptor = - 1 ;
 struct sockaddr_in listen_addr ;
 struct sockaddr_in connect_addr ;
 int size ;
 int saved_errno = - 1 ;
 if ( protocol # ifdef AF_UNIX || family != AF_UNIX # endif ) {
 EVUTIL_SET_SOCKET_ERROR ( WSAEAFNOSUPPORT ) ;
 return - 1 ;
 }
 if ( ! fd ) {
 EVUTIL_SET_SOCKET_ERROR ( WSAEINVAL ) ;
 return - 1 ;
 }
 listener = socket ( AF_INET , type , 0 ) ;
 if ( listener < 0 ) return - 1 ;
 memset ( & listen_addr , 0 , sizeof ( listen_addr ) ) ;
 listen_addr . sin_family = AF_INET ;
 listen_addr . sin_addr . s_addr = htonl ( INADDR_LOOPBACK ) ;
 listen_addr . sin_port = 0 ;
 if ( bind ( listener , ( struct sockaddr * ) & listen_addr , sizeof ( listen_addr ) ) == - 1 ) goto tidy_up_and_fail ;
 if ( listen ( listener , 1 ) == - 1 ) goto tidy_up_and_fail ;
 connector = socket ( AF_INET , type , 0 ) ;
 if ( connector < 0 ) goto tidy_up_and_fail ;
 size = sizeof ( connect_addr ) ;
 if ( getsockname ( listener , ( struct sockaddr * ) & connect_addr , & size ) == - 1 ) goto tidy_up_and_fail ;
 if ( size != sizeof ( connect_addr ) ) goto abort_tidy_up_and_fail ;
 if ( connect ( connector , ( struct sockaddr * ) & connect_addr , sizeof ( connect_addr ) ) == - 1 ) goto tidy_up_and_fail ;
 size = sizeof ( listen_addr ) ;
 acceptor = accept ( listener , ( struct sockaddr * ) & listen_addr , & size ) ;
 if ( acceptor < 0 ) goto tidy_up_and_fail ;
 if ( size != sizeof ( listen_addr ) ) goto abort_tidy_up_and_fail ;
 EVUTIL_CLOSESOCKET ( listener ) ;
 if ( getsockname ( connector , ( struct sockaddr * ) & connect_addr , & size ) == - 1 ) goto tidy_up_and_fail ;
 if ( size != sizeof ( connect_addr ) || listen_addr . sin_family != connect_addr . sin_family || listen_addr . sin_addr . s_addr != connect_addr . sin_addr . s_addr || listen_addr . sin_port != connect_addr . sin_port ) goto abort_tidy_up_and_fail ;
 fd [ 0 ] = connector ;
 fd [ 1 ] = acceptor ;
 return 0 ;
 abort_tidy_up_and_fail : saved_errno = WSAECONNABORTED ;
 tidy_up_and_fail : if ( saved_errno < 0 ) saved_errno = WSAGetLastError ( ) ;
 if ( listener != - 1 ) EVUTIL_CLOSESOCKET ( listener ) ;
 if ( connector != - 1 ) EVUTIL_CLOSESOCKET ( connector ) ;
 if ( acceptor != - 1 ) EVUTIL_CLOSESOCKET ( acceptor ) ;
 EVUTIL_SET_SOCKET_ERROR ( saved_errno ) ;
 return - 1 ;

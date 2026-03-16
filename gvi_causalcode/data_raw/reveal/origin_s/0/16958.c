static socket_handle_t adb_connect ( const char * server_ip , unsigned short * server_tcp_port ) {
 socket_handle_t sock ;
 socklen_t length ;
 struct sockaddr_in server ;
 struct sockaddr_in client ;
 int status ;
 int tries = 0 ;
 memset ( & server , 0x0 , sizeof ( server ) ) ;
 server . sin_family = AF_INET ;
 server . sin_port = GINT16_TO_BE ( * server_tcp_port ) ;
 server . sin_addr . s_addr = inet_addr ( server_ip ) ;
 if ( ( sock = socket ( AF_INET , SOCK_STREAM , IPPROTO_TCP ) ) == INVALID_SOCKET ) {
 errmsg_print ( "ERROR: Cannot open system TCP socket: %s" , strerror ( errno ) ) ;
 return INVALID_SOCKET ;
 }
 useNonBlockingConnectTimeout ( sock ) ;
 while ( tries < SOCKET_CONNECT_TIMEOUT_TRIES ) {
 status = connect ( sock , ( struct sockaddr * ) & server , ( socklen_t ) sizeof ( server ) ) ;
 tries += 1 ;
 if ( status != SOCKET_ERROR ) break ;
 g_usleep ( SOCKET_CONNECT_DELAY_US ) ;
 }
 useNormalConnectTimeout ( sock ) ;
 if ( status == SOCKET_ERROR ) {



 closesocket ( sock ) ;
 return INVALID_SOCKET ;
 }
 ;
 if ( connect ( sock , ( struct sockaddr * ) & server , sizeof ( server ) ) == SOCKET_ERROR ) {
 errmsg_print ( "ERROR: Cannot connect to ADB: <%s> Please check that adb daemon is running." , strerror ( errno ) ) ;
 closesocket ( sock ) ;
 return INVALID_SOCKET ;
 }

 closesocket ( sock ) ;
 return INVALID_SOCKET ;

 if ( verbose ) {
 length = sizeof ( client ) ;
 if ( getsockname ( sock , ( struct sockaddr * ) & client , & length ) ) {
 errmsg_print ( "ERROR getsockname: %s" , strerror ( errno ) ) ;
 closesocket ( sock ) ;
 return INVALID_SOCKET ;
 }
 if ( length != sizeof ( client ) ) {
 errmsg_print ( "ERROR: incorrect length" ) ;
 closesocket ( sock ) ;
 return INVALID_SOCKET ;
 }
 verbose_print ( "VERBOSE: Client port %u\n" , GUINT16_FROM_BE ( client . sin_port ) ) ;
 }
 return sock ;
 }
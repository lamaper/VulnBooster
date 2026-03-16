static my_socket activate_tcp_port ( uint port ) {
 struct addrinfo * ai , * a ;
 struct addrinfo hints ;
 int error ;
 int arg ;
 char port_buf [ NI_MAXSERV ] ;
 my_socket ip_sock = INVALID_SOCKET ;
 DBUG_ENTER ( "activate_tcp_port" ) ;
 DBUG_PRINT ( "general" , ( "IP Socket is %d" , port ) ) ;
 bzero ( & hints , sizeof ( hints ) ) ;
 hints . ai_flags = AI_PASSIVE ;
 hints . ai_socktype = SOCK_STREAM ;
 hints . ai_family = AF_UNSPEC ;
 my_snprintf ( port_buf , NI_MAXSERV , "%d" , port ) ;
 error = getaddrinfo ( my_bind_addr_str , port_buf , & hints , & ai ) ;
 if ( error != 0 ) {
 DBUG_PRINT ( "error" , ( "Got error: %d from getaddrinfo()" , error ) ) ;
 sql_perror ( ER_DEFAULT ( ER_IPSOCK_ERROR ) ) ;
 unireg_abort ( 1 ) ;
 }
 for ( a = ai ;
 a != NULL ;
 a = a -> ai_next ) {
 ip_sock = socket ( a -> ai_family , a -> ai_socktype , a -> ai_protocol ) ;
 char ip_addr [ INET6_ADDRSTRLEN ] ;
 if ( vio_get_normalized_ip_string ( a -> ai_addr , a -> ai_addrlen , ip_addr , sizeof ( ip_addr ) ) ) {
 ip_addr [ 0 ] = 0 ;
 }
 if ( ip_sock == INVALID_SOCKET ) {
 sql_print_error ( "Failed to create a socket for %s '%s': errno: %d." , ( a -> ai_family == AF_INET ) ? "IPv4" : "IPv6" , ( const char * ) ip_addr , ( int ) socket_errno ) ;
 }
 else {
 sql_print_information ( "Server socket created on IP: '%s'." , ( const char * ) ip_addr ) ;
 break ;
 }
 }
 if ( ip_sock == INVALID_SOCKET ) {
 DBUG_PRINT ( "error" , ( "Got error: %d from socket()" , socket_errno ) ) ;
 sql_perror ( ER_DEFAULT ( ER_IPSOCK_ERROR ) ) ;
 unireg_abort ( 1 ) ;
 }

 ( void ) setsockopt ( ip_sock , SOL_SOCKET , SO_REUSEADDR , ( char * ) & arg , sizeof ( arg ) ) ;

 arg = 0 ;
 ( void ) setsockopt ( ip_sock , IPPROTO_IPV6 , IPV6_V6ONLY , ( char * ) & arg , sizeof ( arg ) ) ;
 }

 uint waited , retry , this_wait ;
 for ( waited = 0 , retry = 1 ;
 ;
 retry ++ , waited += this_wait ) {
 if ( ( ( ret = bind ( ip_sock , a -> ai_addr , a -> ai_addrlen ) ) >= 0 ) || ( socket_errno != SOCKET_EADDRINUSE ) || ( waited >= mysqld_port_timeout ) ) break ;
 sql_print_information ( "Retrying bind on TCP/IP port %u" , port ) ;
 this_wait = retry * retry / 3 + 1 ;
 sleep ( this_wait ) ;
 }
 freeaddrinfo ( ai ) ;
 if ( ret < 0 ) {
 char buff [ 100 ] ;
 sprintf ( buff , "Can't start server: Bind on TCP/IP port. Got error: %d" , ( int ) socket_errno ) ;
 sql_perror ( buff ) ;
 sql_print_error ( "Do you already have another mysqld server running on " "port: %u ?" , port ) ;
 unireg_abort ( 1 ) ;
 }
 if ( listen ( ip_sock , ( int ) back_log ) < 0 ) {
 sql_perror ( "Can't start server: listen() on TCP/IP port" ) ;
 sql_print_error ( "listen() on TCP/IP failed with error %d" , socket_errno ) ;
 unireg_abort ( 1 ) ;
 }
 DBUG_RETURN ( ip_sock ) ;
 }
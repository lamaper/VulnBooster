static void configure_tcp ( connection_t * c ) {
 int option ;

 if ( fcntl ( c -> socket , F_SETFL , flags | O_NONBLOCK ) < 0 ) {
 logger ( LOG_ERR , "fcntl for %s: %s" , c -> hostname , strerror ( errno ) ) ;
 }

 if ( ioctlsocket ( c -> socket , FIONBIO , & arg ) != 0 ) {
 logger ( LOG_ERR , "ioctlsocket for %s: %s" , c -> hostname , sockstrerror ( sockerrno ) ) ;
 }

 setsockopt ( c -> socket , SOL_TCP , TCP_NODELAY , ( void * ) & option , sizeof ( option ) ) ;

 setsockopt ( c -> socket , IPPROTO_IP , IP_TOS , ( void * ) & option , sizeof ( option ) ) ;

 setsockopt ( c -> socket , IPPROTO_IPV6 , IPV6_TCLASS , ( void * ) & option , sizeof ( option ) ) ;

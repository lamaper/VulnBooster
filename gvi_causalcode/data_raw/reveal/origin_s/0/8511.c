static void useNormalConnectTimeout ( socket_handle_t sock ) {
 int res_rcv ;

 unsigned long non_blocking = 0 ;
 res_rcv = setsockopt ( sock , SOL_SOCKET , SO_RCVTIMEO , ( const char * ) & socket_timeout , sizeof ( socket_timeout ) ) ;
 ioctlsocket ( sock , FIONBIO , & non_blocking ) ;

 . tv_sec = SOCKET_RW_TIMEOUT_MS / 1000 , . tv_usec = ( SOCKET_RW_TIMEOUT_MS % 1000 ) * 1000 }
 ;
 res_rcv = setsockopt ( sock , SOL_SOCKET , SO_RCVTIMEO , & socket_timeout , sizeof ( socket_timeout ) ) ;

 }
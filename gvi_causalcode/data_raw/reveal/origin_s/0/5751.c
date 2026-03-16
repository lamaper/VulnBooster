static void useNonBlockingConnectTimeout ( socket_handle_t sock ) {
 int res_snd ;
 int res_rcv ;

 unsigned long non_blocking = 1 ;
 res_snd = setsockopt ( sock , SOL_SOCKET , SO_SNDTIMEO , ( const char * ) & socket_timeout , sizeof ( socket_timeout ) ) ;
 res_rcv = setsockopt ( sock , SOL_SOCKET , SO_RCVTIMEO , ( const char * ) & socket_timeout , sizeof ( socket_timeout ) ) ;
 ioctlsocket ( sock , FIONBIO , & non_blocking ) ;

 . tv_sec = SOCKET_RW_TIMEOUT_MS / 1000 , . tv_usec = ( SOCKET_RW_TIMEOUT_MS % 1000 ) * 1000 }
 ;
 res_snd = setsockopt ( sock , SOL_SOCKET , SO_SNDTIMEO , & socket_timeout , sizeof ( socket_timeout ) ) ;
 res_rcv = setsockopt ( sock , SOL_SOCKET , SO_RCVTIMEO , & socket_timeout , sizeof ( socket_timeout ) ) ;

 if ( res_rcv != 0 ) g_debug ( "Can't set socket timeout, using default" ) ;
 }
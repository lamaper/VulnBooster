static void useSndTimeout ( socket_handle_t sock ) {

 setsockopt ( sock , SOL_SOCKET , SO_SNDTIMEO , ( const char * ) & socket_timeout , sizeof ( socket_timeout ) ) ;

 . tv_sec = SOCKET_RW_TIMEOUT_MS / 1000 , . tv_usec = ( SOCKET_RW_TIMEOUT_MS % 1000 ) * 1000 }
 ;
 setsockopt ( sock , SOL_SOCKET , SO_SNDTIMEO , & socket_timeout , sizeof ( socket_timeout ) ) ;

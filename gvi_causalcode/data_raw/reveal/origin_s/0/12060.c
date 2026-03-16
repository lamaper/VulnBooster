static void server_port_read ( struct evdns_server_port * s ) {
 u8 packet [ 1500 ] ;
 struct sockaddr_storage addr ;
 socklen_t addrlen ;
 int r ;
 for ( ;
 ;
 ) {
 addrlen = sizeof ( struct sockaddr_storage ) ;
 r = recvfrom ( s -> socket , packet , sizeof ( packet ) , 0 , ( struct sockaddr * ) & addr , & addrlen ) ;
 if ( r < 0 ) {
 int err = last_error ( s -> socket ) ;
 if ( error_is_eagain ( err ) ) return ;
 log ( EVDNS_LOG_WARN , "Error %s (%d) while reading request." , strerror ( err ) , err ) ;
 return ;
 }
 request_parse ( packet , r , s , ( struct sockaddr * ) & addr , addrlen ) ;
 }
 }
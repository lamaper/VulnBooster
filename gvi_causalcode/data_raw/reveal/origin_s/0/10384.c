static void nameserver_read ( struct nameserver * ns ) {
 u8 packet [ 1500 ] ;
 struct sockaddr_storage ss ;
 socklen_t addrlen = sizeof ( ss ) ;
 for ( ;
 ;
 ) {
 const int r = recvfrom ( ns -> socket , packet , sizeof ( packet ) , 0 , ( struct sockaddr * ) & ss , & addrlen ) ;
 if ( r < 0 ) {
 int err = last_error ( ns -> socket ) ;
 if ( error_is_eagain ( err ) ) return ;
 nameserver_failed ( ns , strerror ( err ) ) ;
 return ;
 }
 if ( ! address_is_correct ( ns , ( struct sockaddr * ) & ss , addrlen ) ) {
 log ( EVDNS_LOG_WARN , "Address mismatch on received " "DNS packet." ) ;
 return ;
 }
 ns -> timedout = 0 ;
 reply_parse ( packet , r ) ;
 }
 }
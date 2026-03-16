static int evdns_request_transmit_to ( struct request * req , struct nameserver * server ) {
 struct sockaddr_in sin ;
 int r ;
 memset ( & sin , 0 , sizeof ( sin ) ) ;
 sin . sin_addr . s_addr = req -> ns -> address ;
 sin . sin_port = req -> ns -> port ;
 sin . sin_family = AF_INET ;
 r = sendto ( server -> socket , req -> request , req -> request_len , 0 , ( struct sockaddr * ) & sin , sizeof ( sin ) ) ;
 if ( r < 0 ) {
 int err = last_error ( server -> socket ) ;
 if ( error_is_eagain ( err ) ) return 1 ;
 nameserver_failed ( req -> ns , strerror ( err ) ) ;
 return 2 ;
 }
 else if ( r != ( int ) req -> request_len ) {
 return 1 ;
 }
 else {
 return 0 ;
 }
 }
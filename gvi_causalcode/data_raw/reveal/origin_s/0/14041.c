static void handle_ns_request ( int dns_fd , struct query * q ) {
 char buf [ 64 * 1024 ] ;
 int len ;
 if ( ns_ip != INADDR_ANY ) {
 memcpy ( & q -> destination . s_addr , & ns_ip , sizeof ( in_addr_t ) ) ;
 }
 len = dns_encode_ns_response ( buf , sizeof ( buf ) , q , topdomain ) ;
 if ( len < 1 ) {
 warnx ( "dns_encode_ns_response doesn't fit" ) ;
 return ;
 }
 if ( debug >= 2 ) {
 fprintf ( stderr , "TX: client %s, type %d, name %s, %d bytes NS reply\n" , format_addr ( & q -> from , q -> fromlen ) , q -> type , q -> name , len ) ;
 }
 if ( sendto ( dns_fd , buf , len , 0 , ( struct sockaddr * ) & q -> from , q -> fromlen ) <= 0 ) {
 warn ( "ns reply send error" ) ;
 }
 }
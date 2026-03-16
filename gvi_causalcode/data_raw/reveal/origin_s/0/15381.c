static void handle_a_request ( int dns_fd , struct query * q , int fakeip ) {
 char buf [ 64 * 1024 ] ;
 int len ;
 if ( fakeip ) {
 in_addr_t ip = inet_addr ( "127.0.0.1" ) ;
 memcpy ( & q -> destination . s_addr , & ip , sizeof ( in_addr_t ) ) ;
 }
 else if ( ns_ip != INADDR_ANY ) {
 memcpy ( & q -> destination . s_addr , & ns_ip , sizeof ( in_addr_t ) ) ;
 }
 len = dns_encode_a_response ( buf , sizeof ( buf ) , q ) ;
 if ( len < 1 ) {
 warnx ( "dns_encode_a_response doesn't fit" ) ;
 return ;
 }
 if ( debug >= 2 ) {
 fprintf ( stderr , "TX: client %s, type %d, name %s, %d bytes A reply\n" , format_addr ( & q -> from , q -> fromlen ) , q -> type , q -> name , len ) ;
 }
 if ( sendto ( dns_fd , buf , len , 0 , ( struct sockaddr * ) & q -> from , q -> fromlen ) <= 0 ) {
 warn ( "a reply send error" ) ;
 }
 }
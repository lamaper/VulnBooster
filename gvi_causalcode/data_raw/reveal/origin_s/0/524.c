static void forward_query ( int bind_fd , struct query * q ) {
 char buf [ 64 * 1024 ] ;
 int len ;
 struct fw_query fwq ;
 struct sockaddr_in * myaddr ;
 in_addr_t newaddr ;
 len = dns_encode ( buf , sizeof ( buf ) , q , QR_QUERY , q -> name , strlen ( q -> name ) ) ;
 if ( len < 1 ) {
 warnx ( "dns_encode doesn't fit" ) ;
 return ;
 }
 memcpy ( & ( fwq . addr ) , & ( q -> from ) , q -> fromlen ) ;
 fwq . addrlen = q -> fromlen ;
 fwq . id = q -> id ;
 fw_query_put ( & fwq ) ;
 newaddr = inet_addr ( "127.0.0.1" ) ;
 myaddr = ( struct sockaddr_in * ) & ( q -> from ) ;
 memcpy ( & ( myaddr -> sin_addr ) , & newaddr , sizeof ( in_addr_t ) ) ;
 myaddr -> sin_port = htons ( bind_port ) ;
 if ( debug >= 2 ) {
 fprintf ( stderr , "TX: NS reply \n" ) ;
 }
 if ( sendto ( bind_fd , buf , len , 0 , ( struct sockaddr * ) & q -> from , q -> fromlen ) <= 0 ) {
 warn ( "forward query error" ) ;
 }
 }
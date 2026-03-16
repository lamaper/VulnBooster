static int tunnel_bind ( int bind_fd , int dns_fd ) {
 char packet [ 64 * 1024 ] ;
 struct sockaddr_storage from ;
 socklen_t fromlen ;
 struct fw_query * query ;
 unsigned short id ;
 int r ;
 fromlen = sizeof ( struct sockaddr ) ;
 r = recvfrom ( bind_fd , packet , sizeof ( packet ) , 0 , ( struct sockaddr * ) & from , & fromlen ) ;
 if ( r <= 0 ) return 0 ;
 id = dns_get_id ( packet , r ) ;
 if ( debug >= 2 ) {
 fprintf ( stderr , "RX: Got response on query %u from DNS\n" , ( id & 0xFFFF ) ) ;
 }
 fw_query_get ( id , & query ) ;
 if ( ! query ) {
 if ( debug >= 2 ) {
 fprintf ( stderr , "Lost sender of id %u, dropping reply\n" , ( id & 0xFFFF ) ) ;
 }
 return 0 ;
 }
 if ( debug >= 2 ) {
 fprintf ( stderr , "TX: client %s id %u, %d bytes\n" , format_addr ( & query -> addr , query -> addrlen ) , ( id & 0xffff ) , r ) ;
 }
 if ( sendto ( dns_fd , packet , r , 0 , ( const struct sockaddr * ) & ( query -> addr ) , query -> addrlen ) <= 0 ) {
 warn ( "forward reply error" ) ;
 }
 return 0 ;
 }
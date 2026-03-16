static void write_dns ( int fd , struct query * q , char * data , int datalen , char downenc ) {
 char buf [ 64 * 1024 ] ;
 int len = 0 ;
 if ( q -> type == T_CNAME || q -> type == T_A ) {
 char cnamebuf [ 1024 ] ;
 write_dns_nameenc ( cnamebuf , sizeof ( cnamebuf ) , data , datalen , downenc ) ;
 len = dns_encode ( buf , sizeof ( buf ) , q , QR_ANSWER , cnamebuf , sizeof ( cnamebuf ) ) ;
 }
 else if ( q -> type == T_MX || q -> type == T_SRV ) {
 char mxbuf [ 64 * 1024 ] ;
 char * b = mxbuf ;
 int offset = 0 ;
 int res ;
 while ( 1 ) {
 res = write_dns_nameenc ( b , sizeof ( mxbuf ) - ( b - mxbuf ) , data + offset , datalen - offset , downenc ) ;
 if ( res < 1 ) {
 b ++ ;
 break ;
 }
 b = b + strlen ( b ) + 1 ;
 offset += res ;
 if ( offset >= datalen ) break ;
 }
 * b = '\0' ;
 len = dns_encode ( buf , sizeof ( buf ) , q , QR_ANSWER , mxbuf , sizeof ( mxbuf ) ) ;
 }
 else if ( q -> type == T_TXT ) {
 char txtbuf [ 64 * 1024 ] ;
 size_t space = sizeof ( txtbuf ) - 1 ;
 ;
 memset ( txtbuf , 0 , sizeof ( txtbuf ) ) ;
 if ( downenc == 'S' ) {
 txtbuf [ 0 ] = 's' ;
 len = b64 -> encode ( txtbuf + 1 , & space , data , datalen ) ;
 }
 else if ( downenc == 'U' ) {
 txtbuf [ 0 ] = 'u' ;
 len = b64u -> encode ( txtbuf + 1 , & space , data , datalen ) ;
 }
 else if ( downenc == 'V' ) {
 txtbuf [ 0 ] = 'v' ;
 len = b128 -> encode ( txtbuf + 1 , & space , data , datalen ) ;
 }
 else if ( downenc == 'R' ) {
 txtbuf [ 0 ] = 'r' ;
 len = MIN ( datalen , sizeof ( txtbuf ) - 1 ) ;
 memcpy ( txtbuf + 1 , data , len ) ;
 }
 else {
 txtbuf [ 0 ] = 't' ;
 len = b32 -> encode ( txtbuf + 1 , & space , data , datalen ) ;
 }
 len = dns_encode ( buf , sizeof ( buf ) , q , QR_ANSWER , txtbuf , len + 1 ) ;
 }
 else {
 len = dns_encode ( buf , sizeof ( buf ) , q , QR_ANSWER , data , datalen ) ;
 }
 if ( len < 1 ) {
 warnx ( "dns_encode doesn't fit" ) ;
 return ;
 }
 if ( debug >= 2 ) {
 fprintf ( stderr , "TX: client %s, type %d, name %s, %d bytes data\n" , format_addr ( & q -> from , q -> fromlen ) , q -> type , q -> name , datalen ) ;
 }
 sendto ( fd , buf , len , 0 , ( struct sockaddr * ) & q -> from , q -> fromlen ) ;
 }
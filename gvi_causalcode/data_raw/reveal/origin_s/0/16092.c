static int get_external_ip ( struct in_addr * ip ) {
 int sock ;
 struct addrinfo * addr ;
 int res ;
 const char * getstr = "GET /ip/ HTTP/1.0\r\n" "Host: api.externalip.net\r\n\r\n" ;
 char buf [ 512 ] ;
 char * b ;
 int len ;
 res = getaddrinfo ( "api.externalip.net" , "80" , NULL , & addr ) ;
 if ( res < 0 ) return 1 ;
 sock = socket ( addr -> ai_family , addr -> ai_socktype , addr -> ai_protocol ) ;
 if ( sock < 0 ) {
 freeaddrinfo ( addr ) ;
 return 2 ;
 }
 res = connect ( sock , addr -> ai_addr , addr -> ai_addrlen ) ;
 freeaddrinfo ( addr ) ;
 if ( res < 0 ) return 3 ;
 res = write ( sock , getstr , strlen ( getstr ) ) ;
 if ( res != strlen ( getstr ) ) return 4 ;
 memset ( buf , 0 , sizeof ( buf ) ) ;
 res = read ( sock , buf , sizeof ( buf ) - 1 ) ;
 if ( res < 0 ) return 5 ;
 len = res ;
 res = close ( sock ) ;
 if ( res < 0 ) return 6 ;
 b = buf ;
 while ( len > 9 ) {
 if ( strncmp ( "\r\n\r\n" , b , 4 ) == 0 ) break ;
 b ++ ;
 len -- ;
 }
 if ( len < 10 ) return 7 ;
 b += 4 ;
 res = inet_aton ( b , ip ) ;
 return ( res == 0 ) ;
 }
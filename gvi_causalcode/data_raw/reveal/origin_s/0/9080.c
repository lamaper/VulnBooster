static int fake_getaddrinfo ( const char * hostname , struct addrinfo * ai ) {
 struct hostent * he = NULL ;
 struct sockaddr_in * sa ;
 if ( hostname ) {
 he = gethostbyname ( hostname ) ;
 if ( ! he ) return ( - 1 ) ;
 }
 ai -> ai_family = he ? he -> h_addrtype : AF_INET ;
 ai -> ai_socktype = SOCK_STREAM ;
 ai -> ai_protocol = 0 ;
 ai -> ai_addrlen = sizeof ( struct sockaddr_in ) ;
 if ( NULL == ( ai -> ai_addr = malloc ( ai -> ai_addrlen ) ) ) return ( - 1 ) ;
 sa = ( struct sockaddr_in * ) ai -> ai_addr ;
 memset ( sa , 0 , ai -> ai_addrlen ) ;
 if ( he ) {
 sa -> sin_family = he -> h_addrtype ;
 memcpy ( & sa -> sin_addr , he -> h_addr_list [ 0 ] , he -> h_length ) ;
 }
 else {
 sa -> sin_family = AF_INET ;
 sa -> sin_addr . s_addr = INADDR_ANY ;
 }
 ai -> ai_next = NULL ;
 return ( 0 ) ;
 }
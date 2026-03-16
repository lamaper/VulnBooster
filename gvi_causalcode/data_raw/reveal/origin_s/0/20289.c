static struct addrinfo * make_addrinfo ( const char * address , u_short port ) {
 struct addrinfo * aitop = NULL ;

 char strport [ NI_MAXSERV ] ;
 int ai_result ;
 memset ( & ai , 0 , sizeof ( ai ) ) ;
 ai . ai_family = AF_INET ;
 ai . ai_socktype = SOCK_STREAM ;
 ai . ai_flags = AI_PASSIVE ;
 evutil_snprintf ( strport , sizeof ( strport ) , "%d" , port ) ;
 if ( ( ai_result = getaddrinfo ( address , strport , & ai , & aitop ) ) != 0 ) {
 if ( ai_result == EAI_SYSTEM ) event_warn ( "getaddrinfo" ) ;
 else event_warnx ( "getaddrinfo: %s" , gai_strerror ( ai_result ) ) ;
 return ( NULL ) ;
 }

 static struct addrinfo ai [ 2 ] ;
 if ( ++ cur == 2 ) cur = 0 ;
 if ( fake_getaddrinfo ( address , & ai [ cur ] ) < 0 ) {
 event_warn ( "fake_getaddrinfo" ) ;
 return ( NULL ) ;
 }
 aitop = & ai [ cur ] ;
 ( ( struct sockaddr_in * ) aitop -> ai_addr ) -> sin_port = htons ( port ) ;

 }
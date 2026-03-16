static int openhost ( const char * hname , int fam ) {
 const char svc [ ] = "ntp" ;
 char temphost [ LENHOSTNAME ] ;
 int a_info , i ;
 struct addrinfo hints , * ai ;
 sockaddr_u addr ;
 size_t octets ;
 register const char * cp ;
 char name [ LENHOSTNAME ] ;
 cp = hname ;
 if ( * cp == '[' ) {
 cp ++ ;
 for ( i = 0 ;
 * cp && * cp != ']' ;
 cp ++ , i ++ ) name [ i ] = * cp ;
 if ( * cp == ']' ) {
 name [ i ] = '\0' ;
 hname = name ;
 }
 else {
 return 0 ;
 }
 }
 ZERO ( hints ) ;
 hints . ai_family = fam ;
 hints . ai_protocol = IPPROTO_UDP ;
 hints . ai_socktype = SOCK_DGRAM ;
 hints . ai_flags = Z_AI_NUMERICHOST ;
 ai = NULL ;
 a_info = getaddrinfo ( hname , svc , & hints , & ai ) ;
 if ( a_info == EAI_NONAME # ifdef EAI_NODATA || a_info == EAI_NODATA # endif ) {
 hints . ai_flags = AI_CANONNAME ;


 }

 hints . ai_flags &= ~ AI_ADDRCONFIG ;
 a_info = getaddrinfo ( hname , svc , & hints , & ai ) ;
 }

 fprintf ( stderr , "%s\n" , gai_strerror ( a_info ) ) ;
 return 0 ;
 }
 INSIST ( ai != NULL ) ;
 ZERO ( addr ) ;
 octets = min ( sizeof ( addr ) , ai -> ai_addrlen ) ;
 memcpy ( & addr , ai -> ai_addr , octets ) ;
 if ( ai -> ai_canonname == NULL ) {
 strlcpy ( temphost , stoa ( & addr ) , sizeof ( temphost ) ) ;
 currenthostisnum = TRUE ;
 }
 else {
 strlcpy ( temphost , ai -> ai_canonname , sizeof ( temphost ) ) ;
 currenthostisnum = FALSE ;
 }
 if ( debug > 2 ) printf ( "Opening host %s (%s)\n" , temphost , ( ai -> ai_family == AF_INET ) ? "AF_INET" : ( ai -> ai_family == AF_INET6 ) ? "AF_INET6" : "AF-???" ) ;
 if ( havehost == 1 ) {
 if ( debug > 2 ) printf ( "Closing old host %s\n" , currenthost ) ;
 closesocket ( sockfd ) ;
 havehost = 0 ;
 }
 strlcpy ( currenthost , temphost , sizeof ( currenthost ) ) ;
 s_port = NSRCPORT ( & addr ) ;

 if ( ai -> ai_family == AF_INET ) * ( struct sockaddr_in * ) & hostaddr = * ( ( struct sockaddr_in * ) ai -> ai_addr ) ;
 else * ( struct sockaddr_in6 * ) & hostaddr = * ( ( struct sockaddr_in6 * ) ai -> ai_addr ) ;

 int optionValue = SO_SYNCHRONOUS_NONALERT ;
 int err ;
 err = setsockopt ( INVALID_SOCKET , SOL_SOCKET , SO_OPENTYPE , ( char * ) & optionValue , sizeof ( optionValue ) ) ;
 if ( err ) {
 mfprintf ( stderr , "setsockopt(SO_SYNCHRONOUS_NONALERT)" " error: %m\n" ) ;
 freeaddrinfo ( ai ) ;
 exit ( 1 ) ;
 }
 }

 if ( sockfd == INVALID_SOCKET ) {
 error ( "socket" ) ;
 freeaddrinfo ( ai ) ;
 return 0 ;
 }

 int rbufsize = DATASIZE + 2048 ;
 if ( setsockopt ( sockfd , SOL_SOCKET , SO_RCVBUF , & rbufsize , sizeof ( int ) ) == - 1 ) error ( "setsockopt" ) ;
 }

 error ( "connect" ) ;
 freeaddrinfo ( ai ) ;
 return 0 ;
 }
 freeaddrinfo ( ai ) ;
 havehost = 1 ;
 numassoc = 0 ;
 return 1 ;
 }
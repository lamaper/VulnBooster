static int fake_getnameinfo ( const struct sockaddr * sa , size_t salen , char * host , size_t hostlen , char * serv , size_t servlen , int flags ) {
 struct sockaddr_in * sin = ( struct sockaddr_in * ) sa ;
 if ( serv != NULL ) {
 char tmpserv [ 16 ] ;
 evutil_snprintf ( tmpserv , sizeof ( tmpserv ) , "%d" , ntohs ( sin -> sin_port ) ) ;
 if ( strlcpy ( serv , tmpserv , servlen ) >= servlen ) return ( - 1 ) ;
 }
 if ( host != NULL ) {
 if ( flags & NI_NUMERICHOST ) {
 if ( strlcpy ( host , inet_ntoa ( sin -> sin_addr ) , hostlen ) >= hostlen ) return ( - 1 ) ;
 else return ( 0 ) ;
 }
 else {
 struct hostent * hp ;
 hp = gethostbyaddr ( ( char * ) & sin -> sin_addr , sizeof ( struct in_addr ) , AF_INET ) ;
 if ( hp == NULL ) return ( - 2 ) ;
 if ( strlcpy ( host , hp -> h_name , hostlen ) >= hostlen ) return ( - 1 ) ;
 else return ( 0 ) ;
 }
 }
 return ( 0 ) ;
 }
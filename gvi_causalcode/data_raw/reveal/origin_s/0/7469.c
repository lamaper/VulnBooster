static int localmom ( void ) {
 static int have_addr = 0 ;
 static struct in_addr hostaddr ;
 struct addrinfo * addr_info ;
 int i ;
 int sock ;
 struct sockaddr_in remote ;
 struct linger ltime ;
 if ( local_conn >= 0 ) {
 return ( local_conn ) ;
 }
 memset ( & remote , 0 , sizeof ( remote ) ) ;
 if ( have_addr == 0 ) {
 if ( pbs_getaddrinfo ( "localhost" , NULL , & addr_info ) != 0 ) {
 TM_DBPRT ( ( "tm_init: localhost not found\n" ) ) return ( - 1 ) ;
 }
 hostaddr = ( ( struct sockaddr_in * ) addr_info -> ai_addr ) -> sin_addr ;
 have_addr = 1 ;
 }
 for ( i = 0 ;
 i < 5 ;
 i ++ ) {
 sock = socket ( AF_INET , SOCK_STREAM , 0 ) ;
 if ( sock < 0 ) {
 return ( - 1 ) ;
 }

 close ( sock ) ;
 return ( - 1 ) ;
 }

 ltime . l_linger = 5 ;
 setsockopt ( sock , SOL_SOCKET , SO_LINGER , & ltime , sizeof ( ltime ) ) ;
 remote . sin_addr = hostaddr ;
 remote . sin_port = htons ( ( unsigned short ) tm_momport ) ;
 remote . sin_family = AF_INET ;
 if ( connect ( sock , ( struct sockaddr * ) & remote , sizeof ( remote ) ) < 0 ) {
 switch ( errno ) {
 case EINTR : case EADDRINUSE : case ETIMEDOUT : case ECONNREFUSED : close ( sock ) ;
 sleep ( 1 ) ;
 continue ;
 break ;
 default : close ( sock ) ;
 return ( - 1 ) ;
 break ;
 }
 }
 else {
 local_conn = sock ;
 break ;
 }
 }
 return ( local_conn ) ;
 }
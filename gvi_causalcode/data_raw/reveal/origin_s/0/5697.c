static void name_from_addr ( struct sockaddr * sa , socklen_t salen , char * * phost , char * * pport ) {
 char ntop [ NI_MAXHOST ] ;
 char strport [ NI_MAXSERV ] ;
 int ni_result ;

 if ( ni_result != 0 ) {
 if ( ni_result == EAI_SYSTEM ) event_err ( 1 , "getnameinfo failed" ) ;
 else event_errx ( 1 , "getnameinfo failed: %s" , gai_strerror ( ni_result ) ) ;
 return ;
 }

 if ( ni_result != 0 ) return ;

 * pport = strdup ( strport ) ;
 }
static int virLogHostnameString ( char * * rawmsg , char * * msg ) {
 char * hoststr ;
 if ( ! virLogHostname ) return - 1 ;
 if ( virAsprintfQuiet ( & hoststr , "hostname: %s" , virLogHostname ) < 0 ) {
 return - 1 ;
 }
 if ( virLogFormatString ( msg , 0 , NULL , VIR_LOG_INFO , hoststr ) < 0 ) {
 VIR_FREE ( hoststr ) ;
 return - 1 ;
 }
 * rawmsg = hoststr ;
 return 0 ;
 }
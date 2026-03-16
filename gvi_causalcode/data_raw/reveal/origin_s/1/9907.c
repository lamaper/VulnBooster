static int virLogHostnameString ( char * * rawmsg , char * * msg ) {
 char * hostname = virGetHostnameQuiet ( ) ;
 char * hoststr ;
 if ( ! hostname ) return - 1 ;
 if ( virAsprintfQuiet ( & hoststr , "hostname: %s" , hostname ) < 0 ) {
 VIR_FREE ( hostname ) ;
 return - 1 ;
 }
 VIR_FREE ( hostname ) ;
 if ( virLogFormatString ( msg , 0 , NULL , VIR_LOG_INFO , hoststr ) < 0 ) {
 VIR_FREE ( hoststr ) ;
 return - 1 ;
 }
 * rawmsg = hoststr ;
 return 0 ;
 }
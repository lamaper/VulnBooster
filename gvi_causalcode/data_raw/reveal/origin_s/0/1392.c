static int virLogVersionString ( const char * * rawmsg , char * * msg ) {
 * rawmsg = VIR_LOG_VERSION_STRING ;
 return virLogFormatString ( msg , 0 , NULL , VIR_LOG_INFO , VIR_LOG_VERSION_STRING ) ;
 }
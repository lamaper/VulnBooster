void remoteDispatchFormatError ( remote_error * rerr , const char * fmt , ... ) {
 va_list args ;
 char msgbuf [ 1024 ] ;
 char * msg = msgbuf ;
 va_start ( args , fmt ) ;
 vsnprintf ( msgbuf , sizeof msgbuf , fmt , args ) ;
 va_end ( args ) ;
 remoteDispatchStringError ( rerr , VIR_ERR_RPC , msg ) ;
 }
static int qemuAgentOpenPty ( const char * monitor ) {
 int monfd ;
 if ( ( monfd = open ( monitor , O_RDWR | O_NONBLOCK ) ) < 0 ) {
 virReportSystemError ( errno , _ ( "Unable to open monitor path %s" ) , monitor ) ;
 return - 1 ;
 }
 if ( virSetCloseExec ( monfd ) < 0 ) {
 virReportSystemError ( errno , "%s" , _ ( "Unable to set monitor close-on-exec flag" ) ) ;
 goto error ;
 }
 return monfd ;
 error : VIR_FORCE_CLOSE ( monfd ) ;
 return - 1 ;
 }
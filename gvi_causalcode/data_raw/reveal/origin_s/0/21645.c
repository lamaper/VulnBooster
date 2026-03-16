static int qemuAgentOpenUnix ( const char * monitor , pid_t cpid , bool * inProgress ) {
 struct sockaddr_un addr ;
 int monfd ;
 virTimeBackOffVar timeout ;
 int ret = - 1 ;
 * inProgress = false ;
 if ( ( monfd = socket ( AF_UNIX , SOCK_STREAM , 0 ) ) < 0 ) {
 virReportSystemError ( errno , "%s" , _ ( "failed to create socket" ) ) ;
 return - 1 ;
 }
 if ( virSetNonBlock ( monfd ) < 0 ) {
 virReportSystemError ( errno , "%s" , _ ( "Unable to put monitor " "into non-blocking mode" ) ) ;
 goto error ;
 }
 if ( virSetCloseExec ( monfd ) < 0 ) {
 virReportSystemError ( errno , "%s" , _ ( "Unable to set monitor " "close-on-exec flag" ) ) ;
 goto error ;
 }
 memset ( & addr , 0 , sizeof ( addr ) ) ;
 addr . sun_family = AF_UNIX ;
 if ( virStrcpyStatic ( addr . sun_path , monitor ) == NULL ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "Agent path %s too big for destination" ) , monitor ) ;
 goto error ;
 }
 if ( virTimeBackOffStart ( & timeout , 1 , 3 * 1000 ) < 0 ) goto error ;
 while ( virTimeBackOffWait ( & timeout ) ) {
 ret = connect ( monfd , ( struct sockaddr * ) & addr , sizeof ( addr ) ) ;
 if ( ret == 0 ) break ;
 if ( ( errno == ENOENT || errno == ECONNREFUSED ) && virProcessKill ( cpid , 0 ) == 0 ) {
 continue ;
 }
 if ( ( errno == EINPROGRESS ) || ( errno == EAGAIN ) ) {
 VIR_DEBUG ( "Connection attempt continuing in background" ) ;
 * inProgress = true ;
 ret = 0 ;
 break ;
 }
 virReportSystemError ( errno , "%s" , _ ( "failed to connect to monitor socket" ) ) ;
 goto error ;
 }
 if ( ret != 0 ) {
 virReportSystemError ( errno , "%s" , _ ( "monitor socket did not show up" ) ) ;
 goto error ;
 }
 return monfd ;
 error : VIR_FORCE_CLOSE ( monfd ) ;
 return - 1 ;
 }
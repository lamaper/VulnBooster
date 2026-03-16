void virLogVMessage ( virLogSourcePtr source , virLogPriority priority , const char * filename , int linenr , const char * funcname , virLogMetadataPtr metadata , const char * fmt , va_list vargs ) {
 static bool logInitMessageStderr = true ;
 char * str = NULL ;
 char * msg = NULL ;
 char timestamp [ VIR_TIME_STRING_BUFLEN ] ;
 int ret ;
 size_t i ;
 int saved_errno = errno ;
 unsigned int filterflags = 0 ;
 if ( virLogInitialize ( ) < 0 ) return ;
 if ( fmt == NULL ) return ;
 if ( source -> serial < virLogFiltersSerial ) virLogSourceUpdate ( source ) ;
 if ( priority < source -> priority ) goto cleanup ;
 filterflags = source -> flags ;
 if ( virVasprintfQuiet ( & str , fmt , vargs ) < 0 ) goto cleanup ;
 ret = virLogFormatString ( & msg , linenr , funcname , priority , str ) ;
 if ( ret < 0 ) goto cleanup ;
 if ( virTimeStringNowRaw ( timestamp ) < 0 ) timestamp [ 0 ] = '\0' ;
 virLogLock ( ) ;
 for ( i = 0 ;
 i < virLogNbOutputs ;
 i ++ ) {
 if ( priority >= virLogOutputs [ i ] -> priority ) {
 if ( virLogOutputs [ i ] -> logInitMessage ) {
 const char * rawinitmsg ;
 char * hoststr = NULL ;
 char * initmsg = NULL ;
 if ( virLogVersionString ( & rawinitmsg , & initmsg ) >= 0 ) virLogOutputs [ i ] -> f ( & virLogSelf , VIR_LOG_INFO , __FILE__ , __LINE__ , __func__ , timestamp , NULL , 0 , rawinitmsg , initmsg , virLogOutputs [ i ] -> data ) ;
 VIR_FREE ( initmsg ) ;
 if ( virLogHostnameString ( & hoststr , & initmsg ) >= 0 ) virLogOutputs [ i ] -> f ( & virLogSelf , VIR_LOG_INFO , __FILE__ , __LINE__ , __func__ , timestamp , NULL , 0 , hoststr , initmsg , virLogOutputs [ i ] -> data ) ;
 VIR_FREE ( hoststr ) ;
 VIR_FREE ( initmsg ) ;
 virLogOutputs [ i ] -> logInitMessage = false ;
 }
 virLogOutputs [ i ] -> f ( source , priority , filename , linenr , funcname , timestamp , metadata , filterflags , str , msg , virLogOutputs [ i ] -> data ) ;
 }
 }
 if ( virLogNbOutputs == 0 ) {
 if ( logInitMessageStderr ) {
 const char * rawinitmsg ;
 char * hoststr = NULL ;
 char * initmsg = NULL ;
 if ( virLogVersionString ( & rawinitmsg , & initmsg ) >= 0 ) virLogOutputToFd ( & virLogSelf , VIR_LOG_INFO , __FILE__ , __LINE__ , __func__ , timestamp , NULL , 0 , rawinitmsg , initmsg , ( void * ) STDERR_FILENO ) ;
 VIR_FREE ( initmsg ) ;
 if ( virLogHostnameString ( & hoststr , & initmsg ) >= 0 ) virLogOutputToFd ( & virLogSelf , VIR_LOG_INFO , __FILE__ , __LINE__ , __func__ , timestamp , NULL , 0 , hoststr , initmsg , ( void * ) STDERR_FILENO ) ;
 VIR_FREE ( hoststr ) ;
 VIR_FREE ( initmsg ) ;
 logInitMessageStderr = false ;
 }
 virLogOutputToFd ( source , priority , filename , linenr , funcname , timestamp , metadata , filterflags , str , msg , ( void * ) STDERR_FILENO ) ;
 }
 virLogUnlock ( ) ;
 cleanup : VIR_FREE ( str ) ;
 VIR_FREE ( msg ) ;
 errno = saved_errno ;
 }
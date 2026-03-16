virLogOutputPtr virLogParseOutput ( const char * src ) {
 virLogOutputPtr ret = NULL ;
 char * * tokens = NULL ;
 char * abspath = NULL ;
 size_t count = 0 ;
 virLogPriority prio ;
 int dest ;
 bool isSUID = virIsSUID ( ) ;
 VIR_DEBUG ( "output=%s" , src ) ;
 if ( ! ( tokens = virStringSplitCount ( src , ":" , 0 , & count ) ) || count < 2 ) {
 virReportError ( VIR_ERR_INVALID_ARG , _ ( "Malformed format for output '%s'" ) , src ) ;
 goto cleanup ;
 }
 if ( virStrToLong_uip ( tokens [ 0 ] , NULL , 10 , & prio ) < 0 || ( prio < VIR_LOG_DEBUG ) || ( prio > VIR_LOG_ERROR ) ) {
 virReportError ( VIR_ERR_INVALID_ARG , _ ( "Invalid priority '%s' for output '%s'" ) , tokens [ 0 ] , src ) ;
 goto cleanup ;
 }
 if ( ( dest = virLogDestinationTypeFromString ( tokens [ 1 ] ) ) < 0 ) {
 virReportError ( VIR_ERR_INVALID_ARG , _ ( "Invalid destination '%s' for output '%s'" ) , tokens [ 1 ] , src ) ;
 goto cleanup ;
 }
 if ( ( ( dest == VIR_LOG_TO_STDERR || dest == VIR_LOG_TO_JOURNALD ) && count != 2 ) || ( ( dest == VIR_LOG_TO_FILE || dest == VIR_LOG_TO_SYSLOG ) && count != 3 ) ) {
 virReportError ( VIR_ERR_INVALID_ARG , _ ( "Output '%s' does not meet the format requirements " "for destination type '%s'" ) , src , tokens [ 1 ] ) ;
 goto cleanup ;
 }
 if ( isSUID && dest != VIR_LOG_TO_STDERR ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Running with SUID permits only destination of type " "'stderr'" ) ) ;
 goto cleanup ;
 }
 switch ( ( virLogDestination ) dest ) {
 case VIR_LOG_TO_STDERR : ret = virLogNewOutputToStderr ( prio ) ;
 break ;
 case VIR_LOG_TO_SYSLOG : # if HAVE_SYSLOG_H ret = virLogNewOutputToSyslog ( prio , tokens [ 2 ] ) ;

 case VIR_LOG_TO_FILE : if ( virFileAbsPath ( tokens [ 2 ] , & abspath ) < 0 ) goto cleanup ;
 ret = virLogNewOutputToFile ( prio , abspath ) ;
 VIR_FREE ( abspath ) ;
 break ;
 case VIR_LOG_TO_JOURNALD : # if USE_JOURNALD ret = virLogNewOutputToJournald ( prio ) ;

 case VIR_LOG_TO_OUTPUT_LAST : break ;
 }
 cleanup : virStringListFree ( tokens ) ;
 return ret ;
 }
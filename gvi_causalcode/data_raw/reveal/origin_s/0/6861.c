int virLogSetDefaultPriority ( virLogPriority priority ) {
 if ( ( priority < VIR_LOG_DEBUG ) || ( priority > VIR_LOG_ERROR ) ) {
 virReportError ( VIR_ERR_INVALID_ARG , _ ( "Failed to set logging priority, argument '%u' is " "invalid" ) , priority ) ;
 return - 1 ;
 }
 if ( virLogInitialize ( ) < 0 ) return - 1 ;
 virLogDefaultPriority = priority ;
 return 0 ;
 }
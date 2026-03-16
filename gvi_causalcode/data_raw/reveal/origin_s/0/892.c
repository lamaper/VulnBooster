virLogOutputPtr virLogOutputNew ( virLogOutputFunc f , virLogCloseFunc c , void * data , virLogPriority priority , virLogDestination dest , const char * name ) {
 virLogOutputPtr ret = NULL ;
 char * ndup = NULL ;
 if ( dest == VIR_LOG_TO_SYSLOG || dest == VIR_LOG_TO_FILE ) {
 if ( ! name ) {
 virReportError ( VIR_ERR_INVALID_ARG , "%s" , _ ( "Missing auxiliary data in output definition" ) ) ;
 return NULL ;
 }
 if ( VIR_STRDUP ( ndup , name ) < 0 ) return NULL ;
 }
 if ( VIR_ALLOC ( ret ) < 0 ) {
 VIR_FREE ( ndup ) ;
 return NULL ;
 }
 ret -> logInitMessage = true ;
 ret -> f = f ;
 ret -> c = c ;
 ret -> data = data ;
 ret -> priority = priority ;
 ret -> dest = dest ;
 ret -> name = ndup ;
 return ret ;
 }
virLogFilterPtr virLogFilterNew ( const char * match , virLogPriority priority , unsigned int flags ) {
 virLogFilterPtr ret = NULL ;
 char * mdup = NULL ;
 virCheckFlags ( VIR_LOG_STACK_TRACE , NULL ) ;
 if ( priority < VIR_LOG_DEBUG || priority > VIR_LOG_ERROR ) {
 virReportError ( VIR_ERR_INVALID_ARG , _ ( "Invalid log priority %d" ) , priority ) ;
 return NULL ;
 }
 if ( VIR_STRDUP_QUIET ( mdup , match ) < 0 ) return NULL ;
 if ( VIR_ALLOC_QUIET ( ret ) < 0 ) {
 VIR_FREE ( mdup ) ;
 return NULL ;
 }
 ret -> match = mdup ;
 ret -> priority = priority ;
 ret -> flags = flags ;
 return ret ;
 }
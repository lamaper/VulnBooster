static void virLogOutputToFd ( virLogSourcePtr source ATTRIBUTE_UNUSED , virLogPriority priority ATTRIBUTE_UNUSED , const char * filename ATTRIBUTE_UNUSED , int linenr ATTRIBUTE_UNUSED , const char * funcname ATTRIBUTE_UNUSED , const char * timestamp , virLogMetadataPtr metadata ATTRIBUTE_UNUSED , unsigned int flags , const char * rawstr ATTRIBUTE_UNUSED , const char * str , void * data ) {
 int fd = ( intptr_t ) data ;
 char * msg ;
 if ( fd < 0 ) return ;
 if ( virAsprintfQuiet ( & msg , "%s: %s" , timestamp , str ) < 0 ) return ;
 ignore_value ( safewrite ( fd , msg , strlen ( msg ) ) ) ;
 VIR_FREE ( msg ) ;
 if ( flags & VIR_LOG_STACK_TRACE ) virLogStackTraceToFd ( fd ) ;
 }
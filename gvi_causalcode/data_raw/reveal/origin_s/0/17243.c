void virLogMessage ( virLogSourcePtr source , virLogPriority priority , const char * filename , int linenr , const char * funcname , virLogMetadataPtr metadata , const char * fmt , ... ) {
 va_list ap ;
 va_start ( ap , fmt ) ;
 virLogVMessage ( source , priority , filename , linenr , funcname , metadata , fmt , ap ) ;
 va_end ( ap ) ;
 }
static int virLogFormatString ( char * * msg , int linenr , const char * funcname , virLogPriority priority , const char * str ) {
 int ret ;
 if ( ( funcname != NULL ) ) {
 ret = virAsprintfQuiet ( msg , "%llu: %s : %s:%d : %s\n" , virThreadSelfID ( ) , virLogPriorityString ( priority ) , funcname , linenr , str ) ;
 }
 else {
 ret = virAsprintfQuiet ( msg , "%llu: %s : %s\n" , virThreadSelfID ( ) , virLogPriorityString ( priority ) , str ) ;
 }
 return ret ;
 }
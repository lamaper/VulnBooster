int mprintf_event ( int evcode , struct peer * p , const char * fmt , ... ) {
 va_list ap ;
 int rc ;
 char msg [ 512 ] ;
 va_start ( ap , fmt ) ;
 rc = mvsnprintf ( msg , sizeof ( msg ) , fmt , ap ) ;
 va_end ( ap ) ;
 report_event ( evcode , p , msg ) ;
 return rc ;
 }
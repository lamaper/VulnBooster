static void die ( const char * format , ... ) {
 va_list arg_ptr ;
 va_start ( arg_ptr , format ) ;
 vfprintf ( stderr , format , arg_ptr ) ;
 va_end ( arg_ptr ) ;
 exit ( 1 ) ;
 }
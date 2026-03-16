static void fail ( const char * format , ... ) {
 va_list arg_ptr ;
 va_start ( arg_ptr , format ) ;
 vfprintf ( stderr , format , arg_ptr ) ;
 va_end ( arg_ptr ) ;
 error_count ++ ;
 }
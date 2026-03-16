static void fail ( const char * format , ... ) {
 va_list arg_ptr ;
 fflush ( stdout ) ;
 fprintf ( stderr , "%s: " , PGM ) ;
 if ( wherestr ) fprintf ( stderr , "%s: " , wherestr ) ;
 va_start ( arg_ptr , format ) ;
 vfprintf ( stderr , format , arg_ptr ) ;
 va_end ( arg_ptr ) ;
 error_count ++ ;
 }
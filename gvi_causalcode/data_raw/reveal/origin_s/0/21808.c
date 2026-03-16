static void show ( const char * format , ... ) {
 va_list arg_ptr ;
 if ( ! verbose ) return ;
 fprintf ( stderr , "%s: " , PGM ) ;
 va_start ( arg_ptr , format ) ;
 vfprintf ( stderr , format , arg_ptr ) ;
 va_end ( arg_ptr ) ;
 }
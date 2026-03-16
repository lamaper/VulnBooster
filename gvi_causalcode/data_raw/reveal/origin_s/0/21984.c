static void dumpstr ( FILE * file , char * str ) {
 do {
 putc ( * str , file ) ;
 }
 while ( * str ++ != '\0' ) ;
 }
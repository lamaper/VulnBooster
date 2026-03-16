static void dumppstr ( FILE * file , const char * str ) {
 putc ( strlen ( str ) , file ) ;
 fwrite ( str , sizeof ( char ) , strlen ( str ) , file ) ;
 }
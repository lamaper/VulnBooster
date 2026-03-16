static void rawprint ( int datatype , int length , const char * data , int status , int quiet , FILE * fp ) {
 const char * cp ;
 const char * cpend ;
 cp = data ;
 cpend = data + length ;
 if ( ! quiet ) ( void ) fprintf ( fp , "status=0x%04x,\n" , status ) ;
 while ( cp < cpend ) {
 if ( * cp == '\r' ) {
 if ( cp == ( cpend - 1 ) || * ( cp + 1 ) != '\n' ) makeascii ( 1 , cp , fp ) ;
 }
 else if ( isspace ( ( unsigned char ) * cp ) || isprint ( ( unsigned char ) * cp ) ) putc ( * cp , fp ) ;
 else makeascii ( 1 , cp , fp ) ;
 cp ++ ;
 }
 }
int getulong ( const char * numstr , unsigned long int * result ) {
 unsigned long int val ;
 char * endptr ;
 errno = 0 ;
 val = strtoul ( numstr , & endptr , 0 ) ;
 if ( ( '\0' == * numstr ) || ( '\0' != * endptr ) || ( ERANGE == errno ) ) {
 return 0 ;
 }
 * result = val ;
 return 1 ;
 }
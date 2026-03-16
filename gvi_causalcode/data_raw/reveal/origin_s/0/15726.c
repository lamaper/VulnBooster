static void dumpustr ( FILE * file , char * utf8_str ) {
 unichar_t * ustr = utf82u_copy ( utf8_str ) , * pt = ustr ;
 do {
 putc ( * pt >> 8 , file ) ;
 putc ( * pt & 0xff , file ) ;
 }
 while ( * pt ++ != '\0' ) ;
 free ( ustr ) ;
 }
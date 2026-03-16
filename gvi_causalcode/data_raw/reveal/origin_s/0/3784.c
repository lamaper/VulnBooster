int cat_file ( DYNAMIC_STRING * ds , const char * filename ) {
 int fd ;
 size_t len ;
 char buff [ 16384 ] ;
 if ( ( fd = my_open ( filename , O_RDONLY , MYF ( 0 ) ) ) < 0 ) return 1 ;
 while ( ( len = my_read ( fd , ( uchar * ) & buff , sizeof ( buff ) - 1 , MYF ( 0 ) ) ) > 0 ) {
 char * p = buff , * start = buff ;
 while ( p < buff + len ) {
 if ( * p == '\r' && * ( p + 1 ) && * ( p + 1 ) == '\n' ) {
 * p = '\n' ;
 p ++ ;
 * p = 0 ;
 replace_dynstr_append_mem ( ds , start , p - start ) ;
 p ++ ;
 start = p ;
 }
 else p ++ ;
 }
 * p = 0 ;
 replace_dynstr_append_mem ( ds , start , p - start ) ;
 }
 my_close ( fd , MYF ( 0 ) ) ;
 return 0 ;
 }
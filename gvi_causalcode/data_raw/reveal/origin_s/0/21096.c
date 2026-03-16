static int main_strtoxoff ( const char * s , xoff_t * xo , char which ) {
 char * e ;
 xoff_t x ;
 XD3_ASSERT ( s && * s != 0 ) ;
 {



 XPR ( NT "-%c: negative integer: %s\n" , which , s ) ;
 return EXIT_FAILURE ;
 }
 x = xx ;
 }
 if ( * e != 0 ) {
 XPR ( NT "-%c: invalid integer: %s\n" , which , s ) ;
 return EXIT_FAILURE ;
 }
 ( * xo ) = x ;
 return 0 ;
 }
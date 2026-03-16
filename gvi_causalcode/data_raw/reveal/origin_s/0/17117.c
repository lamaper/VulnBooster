static void __attribute__ ( ( __format__ ( __printf__ , 1 , 2 ) ) ) error ( const char * fmt , ... ) {
 va_list ap ;
 va_start ( ap , fmt ) ;
 vwarning ( fmt , ap ) ;
 va_end ( ap ) ;
 exit ( 1 ) ;
 }
static void __attribute__ ( ( __format__ ( __printf__ , 1 , 2 ) ) ) warning ( const char * fmt , ... ) {
 va_list ap ;
 va_start ( ap , fmt ) ;
 vwarning ( fmt , ap ) ;
 va_end ( ap ) ;
 }
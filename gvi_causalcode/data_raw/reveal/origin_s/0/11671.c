static void print_md5 ( unsigned char digest [ 16 ] , const char * filename ) {
 int i ;
 for ( i = 0 ;
 i < 16 ;
 ++ i ) printf ( "%02x" , digest [ i ] ) ;
 printf ( " %s\n" , filename ) ;
 }
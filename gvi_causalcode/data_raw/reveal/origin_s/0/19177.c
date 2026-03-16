static int archive_read_format_ar_bid ( struct archive_read * a , int best_bid ) {
 const void * h ;
 ( void ) best_bid ;
 if ( ( h = __archive_read_ahead ( a , 8 , NULL ) ) == NULL ) return ( - 1 ) ;
 if ( memcmp ( h , "!<arch>\n" , 8 ) == 0 ) {
 return ( 64 ) ;
 }
 return ( - 1 ) ;
 }
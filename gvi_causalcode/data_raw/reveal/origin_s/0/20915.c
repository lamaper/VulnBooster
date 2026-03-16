static void _evdns_log ( int warn , const char * fmt , ... ) {
 va_list args ;
 static char buf [ 512 ] ;
 if ( ! evdns_log_fn ) return ;
 va_start ( args , fmt ) ;
 evutil_vsnprintf ( buf , sizeof ( buf ) , fmt , args ) ;
 buf [ sizeof ( buf ) - 1 ] = '\0' ;
 evdns_log_fn ( warn , buf ) ;
 va_end ( args ) ;
 }
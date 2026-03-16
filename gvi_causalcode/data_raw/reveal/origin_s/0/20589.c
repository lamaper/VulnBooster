static void http_highport_test ( void ) {
 int i = - 1 ;
 struct evhttp * myhttp = NULL ;
 fprintf ( stdout , "Testing HTTP Server with high port: " ) ;
 for ( i = 0 ;
 i < 50 ;
 ++ i ) {
 myhttp = evhttp_start ( "127.0.0.1" , 65535 - i ) ;
 if ( myhttp != NULL ) {
 fprintf ( stdout , "OK\n" ) ;
 evhttp_free ( myhttp ) ;
 return ;
 }
 }
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
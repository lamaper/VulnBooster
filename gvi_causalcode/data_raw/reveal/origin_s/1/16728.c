static void test_evbuffer_find ( void ) {
 u_char * p ;
 const char * test1 = "1234567890\r\n" ;
 const char * test2 = "1234567890\r" ;

 unsigned int i ;
 struct evbuffer * buf = evbuffer_new ( ) ;
 fprintf ( stdout , "Testing evbuffer_find 1: " ) ;
 evbuffer_add ( buf , ( u_char * ) test1 , strlen ( test1 ) ) ;
 evbuffer_drain ( buf , strlen ( test1 ) ) ;
 evbuffer_add ( buf , ( u_char * ) test2 , strlen ( test2 ) ) ;
 p = evbuffer_find ( buf , ( u_char * ) "\r\n" , 2 ) ;
 if ( p == NULL ) {
 fprintf ( stdout , "OK\n" ) ;
 }
 else {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 fprintf ( stdout , "Testing evbuffer_find 2: " ) ;
 evbuffer_drain ( buf , strlen ( test2 ) ) ;
 for ( i = 0 ;
 i < EVBUFFER_INITIAL_LENGTH ;
 ++ i ) test3 [ i ] = 'a' ;
 test3 [ EVBUFFER_INITIAL_LENGTH - 1 ] = 'x' ;
 evbuffer_add ( buf , ( u_char * ) test3 , EVBUFFER_INITIAL_LENGTH ) ;
 p = evbuffer_find ( buf , ( u_char * ) "xy" , 2 ) ;
 if ( p == NULL ) {
 printf ( "OK\n" ) ;
 }
 else {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 fprintf ( stdout , "Testing evbuffer_find 3: " ) ;
 p = evbuffer_find ( buf , ( u_char * ) "ax" , 2 ) ;
 if ( p != NULL && strncmp ( ( char * ) p , "ax" , 2 ) == 0 ) {
 printf ( "OK\n" ) ;
 }
 else {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 evbuffer_free ( buf ) ;
 }
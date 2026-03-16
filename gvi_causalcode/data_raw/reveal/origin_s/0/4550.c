static void test_evbuffer ( void ) {
 struct evbuffer * evb = evbuffer_new ( ) ;
 setup_test ( "Testing Evbuffer: " ) ;
 evbuffer_add_printf ( evb , "%s/%d" , "hello" , 1 ) ;
 if ( EVBUFFER_LENGTH ( evb ) == 7 && strcmp ( ( char * ) EVBUFFER_DATA ( evb ) , "hello/1" ) == 0 ) test_ok = 1 ;
 evbuffer_free ( evb ) ;
 cleanup_test ( ) ;
 }
static void test_registerfds ( void ) {
 int i , j ;
 int pair [ 2 ] ;
 struct event read_evs [ 512 ] ;
 struct event write_evs [ 512 ] ;
 struct event_base * base = event_base_new ( ) ;
 fprintf ( stdout , "Testing register fds: " ) ;
 for ( i = 0 ;
 i < 512 ;
 ++ i ) {
 if ( evutil_socketpair ( AF_UNIX , SOCK_STREAM , 0 , pair ) == - 1 ) {
 break ;
 }
 event_set ( & read_evs [ i ] , pair [ 0 ] , EV_READ | EV_PERSIST , simple_read_cb , NULL ) ;
 event_base_set ( base , & read_evs [ i ] ) ;
 event_add ( & read_evs [ i ] , NULL ) ;
 event_set ( & write_evs [ i ] , pair [ 1 ] , EV_WRITE | EV_PERSIST , simple_write_cb , NULL ) ;
 event_base_set ( base , & write_evs [ i ] ) ;
 event_add ( & write_evs [ i ] , NULL ) ;
 event_base_loop ( base , EVLOOP_ONCE ) ;
 }
 for ( j = 0 ;
 j < i ;
 ++ j ) {
 event_del ( & read_evs [ j ] ) ;
 event_del ( & write_evs [ j ] ) ;

 close ( write_evs [ j ] . ev_fd ) ;

 CloseHandle ( ( HANDLE ) write_evs [ j ] . ev_fd ) ;

 }
 event_base_free ( base ) ;
 fprintf ( stdout , "OK\n" ) ;
 }
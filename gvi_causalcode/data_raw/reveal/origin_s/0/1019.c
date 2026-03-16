static void test_signal_pipeloss ( void ) {
 struct event_base * base1 , * base2 ;
 int pipe1 ;
 test_ok = 0 ;
 printf ( "Signal pipeloss: " ) ;
 base1 = event_init ( ) ;
 pipe1 = base1 -> sig . ev_signal_pair [ 0 ] ;
 base2 = event_init ( ) ;
 event_base_free ( base2 ) ;
 event_base_free ( base1 ) ;
 if ( close ( pipe1 ) != - 1 || errno != EBADF ) {
 printf ( "signal pipe not closed. " ) ;
 test_ok = 0 ;
 }
 else {
 test_ok = 1 ;
 }
 cleanup_test ( ) ;
 }
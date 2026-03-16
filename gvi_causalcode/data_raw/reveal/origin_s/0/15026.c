static void test_signal_while_processing ( void ) {
 struct event_base * base = event_init ( ) ;
 struct event ev , ev_timer ;
 struct timeval tv = {
 0 , 0 }
 ;
 setup_test ( "Receiving a signal while processing other signal: " ) ;
 called = - 1 ;
 test_ok = 1 ;
 signal_set ( & ev , SIGUSR1 , signal_cb_swp , NULL ) ;
 signal_add ( & ev , NULL ) ;
 evtimer_set ( & ev_timer , timeout_cb_swp , & ev_timer ) ;
 evtimer_add ( & ev_timer , & tv ) ;
 event_dispatch ( ) ;
 event_base_free ( base ) ;
 cleanup_test ( ) ;
 return ;
 }
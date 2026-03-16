static void test_signal_switchbase ( void ) {
 struct event ev1 , ev2 ;
 struct event_base * base1 , * base2 ;
 int is_kqueue ;
 test_ok = 0 ;
 printf ( "Signal switchbase: " ) ;
 base1 = event_init ( ) ;
 base2 = event_init ( ) ;
 is_kqueue = ! strcmp ( event_get_method ( ) , "kqueue" ) ;
 signal_set ( & ev1 , SIGUSR1 , signal_cb , & ev1 ) ;
 signal_set ( & ev2 , SIGUSR1 , signal_cb , & ev2 ) ;
 if ( event_base_set ( base1 , & ev1 ) || event_base_set ( base2 , & ev2 ) || event_add ( & ev1 , NULL ) || event_add ( & ev2 , NULL ) ) {
 fprintf ( stderr , "%s: cannot set base, add\n" , __func__ ) ;
 exit ( 1 ) ;
 }
 test_ok = 0 ;
 raise ( SIGUSR1 ) ;
 event_base_loop ( base2 , EVLOOP_NONBLOCK ) ;
 if ( is_kqueue ) {
 if ( ! test_ok ) goto done ;
 test_ok = 0 ;
 }
 event_base_loop ( base1 , EVLOOP_NONBLOCK ) ;
 if ( test_ok && ! is_kqueue ) {
 test_ok = 0 ;
 event_base_loop ( base1 , EVLOOP_NONBLOCK ) ;
 raise ( SIGUSR1 ) ;
 event_base_loop ( base1 , EVLOOP_NONBLOCK ) ;
 event_base_loop ( base2 , EVLOOP_NONBLOCK ) ;
 }
 done : event_base_free ( base1 ) ;
 event_base_free ( base2 ) ;
 cleanup_test ( ) ;
 }
static void test_signal_restore ( void ) {
 struct event ev ;
 struct event_base * base = event_init ( ) ;


 printf ( "Signal handler restore: " ) ;

 sa . sa_flags = 0x0 ;
 sigemptyset ( & sa . sa_mask ) ;
 if ( sigaction ( SIGUSR1 , & sa , NULL ) == - 1 ) goto out ;


 signal_add ( & ev , NULL ) ;
 signal_del ( & ev ) ;
 raise ( SIGUSR1 ) ;
 if ( test_ok != 2 ) test_ok = 0 ;
 out : event_base_free ( base ) ;
 cleanup_test ( ) ;
 return ;
 }
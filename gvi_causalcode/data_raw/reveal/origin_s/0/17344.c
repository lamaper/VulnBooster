static void test_fork ( void ) {
 int status , got_sigchld = 0 ;
 struct event ev , sig_ev ;
 pid_t pid ;
 setup_test ( "After fork: " ) ;
 write ( pair [ 0 ] , TEST1 , strlen ( TEST1 ) + 1 ) ;
 event_set ( & ev , pair [ 1 ] , EV_READ , simple_read_cb , & ev ) ;
 if ( event_add ( & ev , NULL ) == - 1 ) exit ( 1 ) ;
 signal_set ( & sig_ev , SIGCHLD , child_signal_cb , & got_sigchld ) ;
 signal_add ( & sig_ev , NULL ) ;
 if ( ( pid = fork ( ) ) == 0 ) {
 if ( event_reinit ( current_base ) == - 1 ) {
 fprintf ( stderr , "FAILED (reinit)\n" ) ;
 exit ( 1 ) ;
 }
 signal_del ( & sig_ev ) ;
 called = 0 ;
 event_dispatch ( ) ;
 exit ( test_ok != 0 || called != 2 ? - 2 : 76 ) ;
 }
 sleep ( 1 ) ;
 write ( pair [ 0 ] , TEST1 , strlen ( TEST1 ) + 1 ) ;
 if ( waitpid ( pid , & status , 0 ) == - 1 ) {
 fprintf ( stderr , "FAILED (fork)\n" ) ;
 exit ( 1 ) ;
 }
 if ( WEXITSTATUS ( status ) != 76 ) {
 fprintf ( stderr , "FAILED (exit): %d\n" , WEXITSTATUS ( status ) ) ;
 exit ( 1 ) ;
 }
 write ( pair [ 0 ] , TEST1 , strlen ( TEST1 ) + 1 ) ;
 shutdown ( pair [ 0 ] , SHUT_WR ) ;
 event_dispatch ( ) ;
 if ( ! got_sigchld ) {
 fprintf ( stdout , "FAILED (sigchld)\n" ) ;
 exit ( 1 ) ;
 }
 signal_del ( & sig_ev ) ;
 cleanup_test ( ) ;
 }
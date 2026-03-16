static void wait_for_signal_thread_to_end ( ) {
 uint i ;
 for ( i = 0 ;
 i < 100 && signal_thread_in_use ;
 i ++ ) {
 if ( pthread_kill ( signal_thread , MYSQL_KILL_SIGNAL ) == ESRCH ) break ;
 my_sleep ( 100 ) ;
 }
 }
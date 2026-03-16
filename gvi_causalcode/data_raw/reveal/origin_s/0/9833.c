pthread_handler_t signal_hand ( void * arg __attribute__ ( ( unused ) ) ) {
 sigset_t set ;
 int sig ;
 my_thread_init ( ) ;
 DBUG_ENTER ( "signal_hand" ) ;
 signal_thread_in_use = 1 ;
 init_thr_alarm ( thread_scheduler -> max_threads + extra_max_connections + global_system_variables . max_insert_delayed_threads + 10 ) ;
 if ( test_flags & TEST_SIGINT ) {
 ( void ) sigemptyset ( & set ) ;
 ( void ) sigaddset ( & set , SIGINT ) ;
 ( void ) pthread_sigmask ( SIG_UNBLOCK , & set , NULL ) ;
 }
 ( void ) sigemptyset ( & set ) ;


 ( void ) sigaddset ( & set , SIGHUP ) ;

 ( void ) sigaddset ( & set , SIGTSTP ) ;
 if ( ! opt_bootstrap ) create_pid_file ( ) ;
 mysql_mutex_lock ( & LOCK_thread_count ) ;
 mysql_mutex_unlock ( & LOCK_thread_count ) ;
 mysql_cond_broadcast ( & COND_thread_count ) ;
 ( void ) pthread_sigmask ( SIG_BLOCK , & set , NULL ) ;
 for ( ;
 ;
 ) {
 int error ;
 if ( shutdown_in_progress && ! abort_loop ) {
 sig = SIGTERM ;
 error = 0 ;
 }
 else while ( ( error = my_sigwait ( & set , & sig ) ) == EINTR ) ;
 if ( cleanup_done ) {
 DBUG_PRINT ( "quit" , ( "signal_handler: calling my_thread_end()" ) ) ;
 my_thread_end ( ) ;
 DBUG_LEAVE ;
 signal_thread_in_use = 0 ;
 pthread_exit ( 0 ) ;
 return 0 ;
 }
 switch ( sig ) {
 case SIGTERM : case SIGQUIT : case SIGKILL : # ifdef EXTRA_DEBUG sql_print_information ( "Got signal %d to shutdown mysqld" , sig ) ;

 DBUG_PRINT ( "info" , ( "Got signal: %d abort_loop: %d" , sig , abort_loop ) ) ;
 if ( ! abort_loop ) {
 abort_loop = 1 ;


 if ( ( error = mysql_thread_create ( 0 , & tmp , & connection_attrib , kill_server_thread , ( void * ) & sig ) ) ) sql_print_error ( "Can't create thread to kill server (errno= %d)" , error ) ;


 break ;
 case SIGHUP : if ( ! abort_loop ) {
 int not_used ;
 mysql_print_status ( ) ;
 reload_acl_and_cache ( ( THD * ) 0 , ( REFRESH_LOG | REFRESH_TABLES | REFRESH_FAST | REFRESH_GRANT | REFRESH_THREADS | REFRESH_HOSTS ) , ( TABLE_LIST * ) 0 , & not_used ) ;
 }
 if ( log_output_options & LOG_NONE ) {
 logger . set_handlers ( LOG_FILE , opt_slow_log ? LOG_TABLE : LOG_NONE , opt_log ? LOG_TABLE : LOG_NONE ) ;
 }
 else {
 logger . set_handlers ( LOG_FILE , opt_slow_log ? log_output_options : LOG_NONE , opt_log ? log_output_options : LOG_NONE ) ;
 }
 break ;

 break ;


 }
 }
 return ( 0 ) ;
 }
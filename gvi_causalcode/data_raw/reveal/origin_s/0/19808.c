static void mysqld_exit ( int exit_code ) {
 wait_for_signal_thread_to_end ( ) ;
 mysql_audit_finalize ( ) ;
 clean_up_mutexes ( ) ;
 clean_up_error_log_mutex ( ) ;
 my_end ( ( opt_endinfo ? MY_CHECK_ERROR | MY_GIVE_INFO : 0 ) ) ;


 }
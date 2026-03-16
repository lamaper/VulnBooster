static void * kill_server ( void * sig_ptr ) # define RETURN_FROM_KILL_SERVER return 0 # else static void __cdecl kill_server ( int sig_ptr ) # define RETURN_FROM_KILL_SERVER return # endif {
 DBUG_ENTER ( "kill_server" ) ;

 if ( kill_in_progress ) {
 DBUG_LEAVE ;
 RETURN_FROM_KILL_SERVER ;
 }
 kill_in_progress = TRUE ;
 abort_loop = 1 ;
 if ( sig != 0 ) my_sigset ( sig , SIG_IGN ) ;
 if ( sig == MYSQL_KILL_SIGNAL || sig == 0 ) sql_print_information ( ER_DEFAULT ( ER_NORMAL_SHUTDOWN ) , my_progname ) ;
 else sql_print_error ( ER_DEFAULT ( ER_GOT_SIGNAL ) , my_progname , sig ) ;

 if ( ! SetEvent ( smem_event_connect_request ) ) {
 DBUG_PRINT ( "error" , ( "Got error: %ld from SetEvent of smem_event_connect_request" , GetLastError ( ) ) ) ;
 }
 }

 if ( sig != MYSQL_KILL_SIGNAL && sig != 0 ) unireg_abort ( 1 ) ;
 else unireg_end ( ) ;
 DBUG_LEAVE ;
 my_thread_end ( ) ;
 pthread_exit ( 0 ) ;
 RETURN_FROM_KILL_SERVER ;

 RETURN_FROM_KILL_SERVER ;

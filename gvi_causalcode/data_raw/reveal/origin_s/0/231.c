void kill_mysql ( void ) {
 DBUG_ENTER ( "kill_mysql" ) ;

 close_server_sock ( ) ;

 if ( ! SetEvent ( hEventShutdown ) ) {
 DBUG_PRINT ( "error" , ( "Got error: %ld from SetEvent" , GetLastError ( ) ) ) ;
 }
 }

 DBUG_PRINT ( "error" , ( "Got error %d from pthread_kill" , errno ) ) ;
 }


 shutdown_in_progress = 1 ;

 pthread_t tmp ;
 int error ;
 abort_loop = 1 ;
 if ( ( error = mysql_thread_create ( 0 , & tmp , & connection_attrib , kill_server_thread , ( void * ) 0 ) ) ) sql_print_error ( "Can't create thread to kill server (errno= %d)." , error ) ;
 }

 }
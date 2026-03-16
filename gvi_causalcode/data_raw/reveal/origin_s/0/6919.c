static void create_shutdown_thread ( ) {

 pthread_t hThread ;
 int error ;
 if ( ( error = mysql_thread_create ( key_thread_handle_shutdown , & hThread , & connection_attrib , handle_shutdown , 0 ) ) ) sql_print_warning ( "Can't create thread to handle shutdown requests" " (errno= %d)" , error ) ;
 Service . SetShutdownEvent ( hEventShutdown ) ;

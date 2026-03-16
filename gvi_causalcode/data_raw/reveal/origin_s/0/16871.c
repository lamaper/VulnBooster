sig_handler handle_sigint ( int sig ) {
 char kill_buffer [ 40 ] ;
 MYSQL * kill_mysql = NULL ;
 if ( ! executing_query || ( interrupted_query == 2 ) ) {
 tee_fprintf ( stdout , "Ctrl-C -- exit!\n" ) ;
 goto err ;
 }
 kill_mysql = mysql_init ( kill_mysql ) ;
 if ( ! mysql_real_connect ( kill_mysql , current_host , current_user , opt_password , "" , opt_mysql_port , opt_mysql_unix_port , 0 ) ) {
 tee_fprintf ( stdout , "Ctrl-C -- sorry, cannot connect to server to kill query, giving up ...\n" ) ;
 goto err ;
 }
 interrupted_query ++ ;
 if ( ( interrupted_query == 1 ) && ( mysql_get_server_version ( & mysql ) < 50000 ) ) interrupted_query = 2 ;
 sprintf ( kill_buffer , "KILL %s%lu" , ( interrupted_query == 1 ) ? "QUERY " : "" , mysql_thread_id ( & mysql ) ) ;
 if ( verbose ) tee_fprintf ( stdout , "Ctrl-C -- sending \"%s\" to server ...\n" , kill_buffer ) ;
 mysql_real_query ( kill_mysql , kill_buffer , ( uint ) strlen ( kill_buffer ) ) ;
 mysql_close ( kill_mysql ) ;
 tee_fprintf ( stdout , "Ctrl-C -- query killed. Continuing normally.\n" ) ;
 if ( in_com_source ) aborted = 1 ;
 return ;
 err : # ifdef _WIN32 mysql_thread_end ( ) ;


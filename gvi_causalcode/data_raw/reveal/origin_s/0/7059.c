bool start_postmaster ( ClusterInfo * cluster , bool throw_error ) {
 char cmd [ MAXPGPATH * 4 + 1000 ] ;
 PGconn * conn ;
 bool pg_ctl_return = false ;
 char socket_string [ MAXPGPATH + 200 ] ;
 static bool exit_hook_registered = false ;
 if ( ! exit_hook_registered ) {
 atexit ( stop_postmaster_atexit ) ;
 exit_hook_registered = true ;
 }
 socket_string [ 0 ] = '\0' ;

 if ( cluster -> sockdir ) snprintf ( socket_string + strlen ( socket_string ) , sizeof ( socket_string ) - strlen ( socket_string ) , " -c %s='%s'" , ( GET_MAJOR_VERSION ( cluster -> major_version ) < 903 ) ? "unix_socket_directory" : "unix_socket_directories" , cluster -> sockdir ) ;

 pg_ctl_return = exec_prog ( SERVER_START_LOG_FILE , ( strcmp ( SERVER_LOG_FILE , SERVER_START_LOG_FILE ) != 0 ) ? SERVER_LOG_FILE : NULL , false , "%s" , cmd ) ;
 if ( ! pg_ctl_return && ! throw_error ) return false ;
 if ( pg_ctl_return ) os_info . running_cluster = cluster ;
 if ( ( conn = get_db_conn ( cluster , "template1" ) ) == NULL || PQstatus ( conn ) != CONNECTION_OK ) {
 pg_log ( PG_REPORT , "\nconnection to database failed: %s\n" , PQerrorMessage ( conn ) ) ;
 if ( conn ) PQfinish ( conn ) ;
 pg_fatal ( "could not connect to %s postmaster started with the command:\n" "%s\n" , CLUSTER_NAME ( cluster ) , cmd ) ;
 }
 PQfinish ( conn ) ;
 if ( ! pg_ctl_return ) pg_fatal ( "pg_ctl failed to start the %s server, or connection failed\n" , CLUSTER_NAME ( cluster ) ) ;
 return true ;
 }
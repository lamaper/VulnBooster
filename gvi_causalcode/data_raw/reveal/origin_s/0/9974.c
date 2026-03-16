static int com_status ( String * buffer __attribute__ ( ( unused ) ) , char * line __attribute__ ( ( unused ) ) ) {
 const char * status_str ;
 char buff [ 40 ] ;
 ulonglong id ;
 MYSQL_RES * result ;
 LINT_INIT ( result ) ;
 if ( mysql_real_query_for_lazy ( C_STRING_WITH_LEN ( "select DATABASE(), USER() limit 1" ) ) ) return 0 ;
 tee_puts ( "--------------" , stdout ) ;
 usage ( 1 ) ;
 tee_fprintf ( stdout , "\nConnection id:\t\t%lu\n" , mysql_thread_id ( & mysql ) ) ;
 if ( ! mysql_store_result_for_lazy ( & result ) ) {
 MYSQL_ROW cur = mysql_fetch_row ( result ) ;
 if ( cur ) {
 tee_fprintf ( stdout , "Current database:\t%s\n" , cur [ 0 ] ? cur [ 0 ] : "" ) ;
 tee_fprintf ( stdout , "Current user:\t\t%s\n" , cur [ 1 ] ) ;
 }
 mysql_free_result ( result ) ;
 }

 else # endif tee_puts ( "SSL:\t\t\tNot in use" , stdout ) ;
 if ( skip_updates ) {
 my_vidattr ( A_BOLD ) ;
 tee_fprintf ( stdout , "\nAll updates ignored to this database\n" ) ;
 my_vidattr ( A_NORMAL ) ;
 }

 tee_fprintf ( stdout , "Using outfile:\t\t'%s'\n" , opt_outfile ? outfile : "" ) ;

 tee_fprintf ( stdout , "Server:\t\t\t%s\n" , mysql_get_server_name ( & mysql ) ) ;
 tee_fprintf ( stdout , "Server version:\t\t%s\n" , server_version_string ( & mysql ) ) ;
 tee_fprintf ( stdout , "Protocol version:\t%d\n" , mysql_get_proto_info ( & mysql ) ) ;
 tee_fprintf ( stdout , "Connection:\t\t%s\n" , mysql_get_host_info ( & mysql ) ) ;
 if ( ( id = mysql_insert_id ( & mysql ) ) ) tee_fprintf ( stdout , "Insert id:\t\t%s\n" , llstr ( id , buff ) ) ;
 if ( mysql_real_query_for_lazy ( C_STRING_WITH_LEN ( "select @@character_set_client, @@character_set_connection, " "@@character_set_server, @@character_set_database limit 1" ) ) ) {
 if ( mysql_errno ( & mysql ) == CR_SERVER_GONE_ERROR ) return 0 ;
 }
 if ( ! mysql_store_result_for_lazy ( & result ) ) {
 MYSQL_ROW cur = mysql_fetch_row ( result ) ;
 if ( cur ) {
 tee_fprintf ( stdout , "Server characterset:\t%s\n" , cur [ 2 ] ? cur [ 2 ] : "" ) ;
 tee_fprintf ( stdout , "Db characterset:\t%s\n" , cur [ 3 ] ? cur [ 3 ] : "" ) ;
 tee_fprintf ( stdout , "Client characterset:\t%s\n" , cur [ 0 ] ? cur [ 0 ] : "" ) ;
 tee_fprintf ( stdout , "Conn. characterset:\t%s\n" , cur [ 1 ] ? cur [ 1 ] : "" ) ;
 }
 mysql_free_result ( result ) ;
 }
 else {
 tee_fprintf ( stdout , "Client characterset:\t%s\n" , charset_info -> csname ) ;
 tee_fprintf ( stdout , "Server characterset:\t%s\n" , mysql . charset -> csname ) ;
 }

 else tee_fprintf ( stdout , "UNIX socket:\t\t%s\n" , mysql . unix_socket ) ;
 if ( mysql . net . compress ) tee_fprintf ( stdout , "Protocol:\t\tCompressed\n" ) ;

 ulong sec ;
 const char * pos = strchr ( status_str , ' ' ) ;
 tee_fprintf ( stdout , "%.*s\t\t\t" , ( int ) ( pos - status_str ) , status_str ) ;
 if ( ( status_str = str2int ( pos , 10 , 0 , LONG_MAX , ( long * ) & sec ) ) ) {
 nice_time ( ( double ) sec , buff , 0 ) ;
 tee_puts ( buff , stdout ) ;
 while ( * status_str == ' ' ) status_str ++ ;
 tee_putc ( '\n' , stdout ) ;
 tee_puts ( status_str , stdout ) ;
 }
 }
 if ( safe_updates ) {
 my_vidattr ( A_BOLD ) ;
 tee_fprintf ( stdout , "\nNote that you are running in safe_update_mode:\n" ) ;
 my_vidattr ( A_NORMAL ) ;
 tee_fprintf ( stdout , "\ UPDATEs and DELETEs that don't use a key in the WHERE clause are not allowed.\n\ (One can force an UPDATE/DELETE by adding LIMIT # at the end of the command.)\n\ SELECT has an automatic 'LIMIT %lu' if LIMIT is not used.\n\ Max number of examined row combination in a join is set to: %lu\n\n" , select_limit , max_join_size ) ;
 }
 tee_puts ( "--------------\n" , stdout ) ;
 return 0 ;
 }
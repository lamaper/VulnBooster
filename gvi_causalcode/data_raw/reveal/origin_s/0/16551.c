static void test_bug43560 ( void ) {
 MYSQL * conn ;
 uint rc ;
 MYSQL_STMT * stmt = 0 ;
 MYSQL_BIND bind ;
 my_bool is_null = 0 ;
 char buffer [ 256 ] ;
 const uint BUFSIZE = sizeof ( buffer ) ;
 const char * values [ ] = {
 "eins" , "zwei" , "drei" , "viele" , NULL }
 ;
 const char insert_str [ ] = "INSERT INTO t1 (c2) VALUES (?)" ;
 unsigned long length ;
 const unsigned int drop_db = opt_drop_db ;
 DBUG_ENTER ( "test_bug43560" ) ;
 myheader ( "test_bug43560" ) ;
 if ( ! strstr ( mysql -> server_version , "debug" ) ) {
 fprintf ( stdout , "Skipping test_bug43560: server not DEBUG version\n" ) ;
 DBUG_VOID_RETURN ;
 }
 conn = client_connect ( 0 , MYSQL_PROTOCOL_TCP , 0 ) ;
 rc = mysql_query ( conn , "DROP TABLE IF EXISTS t1" ) ;
 myquery ( rc ) ;
 rc = mysql_query ( conn , "CREATE TABLE t1 (c1 INT PRIMARY KEY AUTO_INCREMENT, c2 CHAR(10))" ) ;
 myquery ( rc ) ;
 stmt = mysql_stmt_init ( conn ) ;
 check_stmt ( stmt ) ;
 rc = mysql_stmt_prepare ( stmt , insert_str , strlen ( insert_str ) ) ;
 check_execute ( stmt , rc ) ;
 memset ( & bind , 0 , sizeof ( bind ) ) ;
 bind . buffer_type = MYSQL_TYPE_STRING ;
 bind . buffer_length = BUFSIZE ;
 bind . buffer = buffer ;
 bind . is_null = & is_null ;
 bind . length = & length ;
 rc = mysql_stmt_bind_param ( stmt , & bind ) ;
 check_execute ( stmt , rc ) ;
 strncpy ( buffer , values [ 0 ] , BUFSIZE ) ;
 length = strlen ( buffer ) ;
 rc = mysql_stmt_execute ( stmt ) ;
 check_execute ( stmt , rc ) ;
 rc = mysql_query ( conn , "SET SESSION debug='+d,close_conn_after_stmt_execute'" ) ;
 myquery ( rc ) ;
 strncpy ( buffer , values [ 1 ] , BUFSIZE ) ;
 length = strlen ( buffer ) ;
 rc = mysql_stmt_execute ( stmt ) ;
 DIE_UNLESS ( rc && mysql_stmt_errno ( stmt ) == CR_SERVER_LOST ) ;
 strncpy ( buffer , values [ 2 ] , BUFSIZE ) ;
 length = strlen ( buffer ) ;
 rc = mysql_stmt_execute ( stmt ) ;
 DIE_UNLESS ( rc && mysql_stmt_errno ( stmt ) == CR_SERVER_LOST ) ;
 mysql_stmt_close ( stmt ) ;
 opt_drop_db = 0 ;
 client_disconnect ( conn ) ;
 rc = mysql_query ( mysql , "DROP TABLE t1" ) ;
 myquery ( rc ) ;
 opt_drop_db = drop_db ;
 DBUG_VOID_RETURN ;
 }
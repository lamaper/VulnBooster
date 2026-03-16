static void test_bug54041_impl ( ) {
 int rc ;
 MYSQL_STMT * stmt ;
 MYSQL_BIND bind ;
 DBUG_ENTER ( "test_bug54041" ) ;
 myheader ( "test_bug54041" ) ;
 rc = mysql_query ( mysql , "DROP TABLE IF EXISTS t1" ) ;
 myquery ( rc ) ;
 rc = mysql_query ( mysql , "CREATE TABLE t1 (a INT)" ) ;
 myquery ( rc ) ;
 stmt = mysql_simple_prepare ( mysql , "SELECT a FROM t1 WHERE a > ?" ) ;
 check_stmt ( stmt ) ;
 verify_param_count ( stmt , 1 ) ;
 memset ( & bind , 0 , sizeof ( bind ) ) ;
 bind . buffer_type = MYSQL_TYPE_LONG ;
 rc = mysql_stmt_bind_param ( stmt , & bind ) ;
 check_execute ( stmt , rc ) ;
 stmt -> params [ 0 ] . buffer_type = MYSQL_TYPE_STRING ;
 rc = mysql_stmt_send_long_data ( stmt , 0 , "data" , 5 ) ;
 check_execute ( stmt , rc ) ;
 stmt -> params [ 0 ] . buffer_type = MYSQL_TYPE_LONG ;
 rc = mysql_stmt_execute ( stmt ) ;
 check_execute_r ( stmt , rc ) ;
 mysql_stmt_close ( stmt ) ;
 rc = mysql_query ( mysql , "DROP TABLE IF EXISTS t1" ) ;
 myquery ( rc ) ;
 DBUG_VOID_RETURN ;
 }
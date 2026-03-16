static void test_bug4236 ( ) {
 MYSQL_STMT * stmt ;
 const char * stmt_text ;
 int rc ;
 MYSQL_STMT backup ;
 myheader ( "test_bug4236" ) ;
 stmt = mysql_stmt_init ( mysql ) ;
 stmt_text = "SELECT 1" ;
 rc = mysql_stmt_prepare ( stmt , stmt_text , strlen ( stmt_text ) ) ;
 check_execute ( stmt , rc ) ;
 backup . stmt_id = stmt -> stmt_id ;
 stmt -> stmt_id = 0 ;
 rc = mysql_stmt_execute ( stmt ) ;
 DIE_UNLESS ( rc ) ;
 stmt -> stmt_id = backup . stmt_id ;
 mysql_stmt_close ( stmt ) ;
 }
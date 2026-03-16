static void test_bug7990 ( ) {
 MYSQL_STMT * stmt ;
 int rc ;
 myheader ( "test_bug7990" ) ;
 stmt = mysql_stmt_init ( mysql ) ;
 rc = mysql_stmt_prepare ( stmt , "foo" , 3 ) ;
 DIE_UNLESS ( rc && mysql_stmt_errno ( stmt ) && mysql_errno ( mysql ) ) ;
 mysql_stmt_close ( stmt ) ;
 DIE_UNLESS ( ! mysql_errno ( mysql ) ) ;
 }
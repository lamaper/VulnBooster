static void test_bug16143 ( ) {
 MYSQL_STMT * stmt ;
 myheader ( "test_bug16143" ) ;
 stmt = mysql_stmt_init ( mysql ) ;
 DIE_UNLESS ( strcmp ( mysql_stmt_sqlstate ( stmt ) , "00000" ) == 0 ) ;
 mysql_stmt_close ( stmt ) ;
 }
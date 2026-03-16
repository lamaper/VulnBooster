static void test_bug45010 ( ) {
 int rc ;
 const char query1 [ ] = "select a.\x80" , query2 [ ] = "describe `table\xef" ;
 DBUG_ENTER ( "test_bug45010" ) ;
 myheader ( "test_bug45010" ) ;
 rc = mysql_query ( mysql , "set names utf8" ) ;
 myquery ( rc ) ;
 rc = mysql_real_query ( mysql , query1 , sizeof ( query1 ) - 1 ) ;
 DIE_UNLESS ( rc ) ;
 rc = mysql_real_query ( mysql , query2 , sizeof ( query2 ) - 1 ) ;
 DIE_UNLESS ( rc ) ;
 rc = mysql_query ( mysql , "set names default" ) ;
 myquery ( rc ) ;
 DBUG_VOID_RETURN ;
 }
static void client_store_result ( ) {
 MYSQL_RES * result ;
 int rc ;
 myheader ( "client_store_result" ) ;
 rc = mysql_query ( mysql , "SELECT * FROM t1" ) ;
 myquery ( rc ) ;
 result = mysql_store_result ( mysql ) ;
 mytest ( result ) ;
 ( void ) my_process_result_set ( result ) ;
 mysql_free_result ( result ) ;
 }
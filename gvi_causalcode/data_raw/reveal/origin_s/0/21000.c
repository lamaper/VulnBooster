static int do_stop_slave_sql ( MYSQL * mysql_con ) {
 MYSQL_RES * slave ;
 if ( mysql_query_with_error_report ( mysql_con , & slave , "SHOW SLAVE STATUS" ) ) return ( 1 ) ;
 else {
 MYSQL_ROW row = mysql_fetch_row ( slave ) ;
 if ( row && row [ 11 ] ) {
 if ( ! strcmp ( row [ 11 ] , "No" ) ) {
 mysql_free_result ( slave ) ;
 return ( 0 ) ;
 }
 }
 }
 mysql_free_result ( slave ) ;
 if ( mysql_query_with_error_report ( mysql_con , 0 , "STOP SLAVE SQL_THREAD" ) ) return ( 1 ) ;
 return ( 0 ) ;
 }
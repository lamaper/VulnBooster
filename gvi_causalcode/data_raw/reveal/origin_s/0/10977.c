static void get_current_db ( ) {
 MYSQL_RES * res ;
 if ( one_database ) return ;
 my_free ( current_db ) ;
 current_db = NULL ;
 if ( ! mysql_query ( & mysql , "SELECT DATABASE()" ) && ( res = mysql_use_result ( & mysql ) ) ) {
 MYSQL_ROW row = mysql_fetch_row ( res ) ;
 if ( row && row [ 0 ] ) current_db = my_strdup ( row [ 0 ] , MYF ( MY_WME ) ) ;
 mysql_free_result ( res ) ;
 }
 }
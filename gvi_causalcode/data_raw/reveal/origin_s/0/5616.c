static void init_username ( ) {
 my_free ( full_username ) ;
 my_free ( part_username ) ;
 MYSQL_RES * result ;
 LINT_INIT ( result ) ;
 if ( ! mysql_query ( & mysql , "select USER()" ) && ( result = mysql_use_result ( & mysql ) ) ) {
 MYSQL_ROW cur = mysql_fetch_row ( result ) ;
 full_username = my_strdup ( cur [ 0 ] , MYF ( MY_WME ) ) ;
 part_username = my_strdup ( strtok ( cur [ 0 ] , "@" ) , MYF ( MY_WME ) ) ;
 ( void ) mysql_fetch_row ( result ) ;
 }
 }
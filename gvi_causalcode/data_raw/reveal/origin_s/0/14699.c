static void show_warnings_before_error ( MYSQL * mysql ) {
 MYSQL_RES * res ;
 const char * query = "SHOW WARNINGS" ;
 DBUG_ENTER ( "show_warnings_before_error" ) ;
 if ( ! mysql ) DBUG_VOID_RETURN ;
 if ( mysql_query ( mysql , query ) ) {
 log_msg ( "Error running query '%s': %d %s" , query , mysql_errno ( mysql ) , mysql_error ( mysql ) ) ;
 DBUG_VOID_RETURN ;
 }
 if ( ( res = mysql_store_result ( mysql ) ) == NULL ) {
 DBUG_VOID_RETURN ;
 }
 if ( mysql_num_rows ( res ) <= 1 ) {
 }
 else {
 MYSQL_ROW row ;
 unsigned int row_num = 0 ;
 unsigned int num_fields = mysql_num_fields ( res ) ;
 fprintf ( stderr , "\nWarnings from just before the error:\n" ) ;
 while ( ( row = mysql_fetch_row ( res ) ) ) {
 unsigned int i ;
 unsigned long * lengths = mysql_fetch_lengths ( res ) ;
 if ( ++ row_num >= mysql_num_rows ( res ) ) {
 break ;
 }
 for ( i = 0 ;
 i < num_fields ;
 i ++ ) {
 fprintf ( stderr , "%.*s " , ( int ) lengths [ i ] , row [ i ] ? row [ i ] : "NULL" ) ;
 }
 fprintf ( stderr , "\n" ) ;
 }
 }
 mysql_free_result ( res ) ;
 DBUG_VOID_RETURN ;
 }
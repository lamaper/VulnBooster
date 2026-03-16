static int fetch_db_collation ( const char * db_name , char * db_cl_name , int db_cl_size ) {
 my_bool err_status = FALSE ;
 MYSQL_RES * db_cl_res ;
 MYSQL_ROW db_cl_row ;
 if ( mysql_select_db ( mysql , db_name ) ) {
 DB_error ( mysql , "when selecting the database" ) ;
 return 1 ;
 }
 if ( mysql_query_with_error_report ( mysql , & db_cl_res , "select @@collation_database" ) ) return 1 ;
 do {
 if ( mysql_num_rows ( db_cl_res ) != 1 ) {
 err_status = TRUE ;
 break ;
 }
 if ( ! ( db_cl_row = mysql_fetch_row ( db_cl_res ) ) ) {
 err_status = TRUE ;
 break ;
 }
 strncpy ( db_cl_name , db_cl_row [ 0 ] , db_cl_size - 1 ) ;
 db_cl_name [ db_cl_size - 1 ] = 0 ;
 }
 while ( FALSE ) ;
 mysql_free_result ( db_cl_res ) ;
 return err_status ? 1 : 0 ;
 }
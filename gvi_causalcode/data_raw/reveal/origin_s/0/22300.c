static char * primary_key_fields ( const char * table_name ) {
 MYSQL_RES * res = NULL ;
 MYSQL_ROW row ;
 char show_keys_buff [ 15 + NAME_LEN * 2 + 3 ] ;
 uint result_length = 0 ;
 char * result = 0 ;
 char buff [ NAME_LEN * 2 + 3 ] ;
 char * quoted_field ;
 my_snprintf ( show_keys_buff , sizeof ( show_keys_buff ) , "SHOW KEYS FROM %s" , table_name ) ;
 if ( mysql_query ( mysql , show_keys_buff ) || ! ( res = mysql_store_result ( mysql ) ) ) {
 fprintf ( stderr , "Warning: Couldn't read keys from table %s;
" " records are NOT sorted (%s)\n" , table_name , mysql_error ( mysql ) ) ;
 goto cleanup ;
 }
 if ( ( row = mysql_fetch_row ( res ) ) && atoi ( row [ 1 ] ) == 0 ) {
 do {
 quoted_field = quote_name ( row [ 4 ] , buff , 0 ) ;
 result_length += strlen ( quoted_field ) + 1 ;
 }
 while ( ( row = mysql_fetch_row ( res ) ) && atoi ( row [ 3 ] ) > 1 ) ;
 }
 if ( result_length ) {
 char * end ;
 result = my_malloc ( result_length + 10 , MYF ( MY_WME ) ) ;
 if ( ! result ) {
 fprintf ( stderr , "Error: Not enough memory to store ORDER BY clause\n" ) ;
 goto cleanup ;
 }
 mysql_data_seek ( res , 0 ) ;
 row = mysql_fetch_row ( res ) ;
 quoted_field = quote_name ( row [ 4 ] , buff , 0 ) ;
 end = strmov ( result , quoted_field ) ;
 while ( ( row = mysql_fetch_row ( res ) ) && atoi ( row [ 3 ] ) > 1 ) {
 quoted_field = quote_name ( row [ 4 ] , buff , 0 ) ;
 end = strxmov ( end , "," , quoted_field , NullS ) ;
 }
 }
 cleanup : if ( res ) mysql_free_result ( res ) ;
 return result ;
 }
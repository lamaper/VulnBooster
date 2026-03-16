void run_query_normal ( struct st_connection * cn , struct st_command * command , int flags , char * query , int query_len , DYNAMIC_STRING * ds , DYNAMIC_STRING * ds_warnings ) {
 MYSQL_RES * res = 0 ;
 MYSQL * mysql = cn -> mysql ;
 int err = 0 , counter = 0 ;
 DBUG_ENTER ( "run_query_normal" ) ;
 DBUG_PRINT ( "enter" , ( "flags: %d" , flags ) ) ;
 DBUG_PRINT ( "enter" , ( "query: '%-.60s'" , query ) ) ;
 if ( ! mysql ) {
 handle_no_active_connection ( command , cn , ds ) ;
 DBUG_VOID_RETURN ;
 }
 if ( flags & QUERY_SEND_FLAG ) {
 if ( do_send_query ( cn , query , query_len ) ) {
 handle_error ( command , mysql_errno ( mysql ) , mysql_error ( mysql ) , mysql_sqlstate ( mysql ) , ds ) ;
 goto end ;
 }
 }
 if ( ! ( flags & QUERY_REAP_FLAG ) ) {
 cn -> pending = TRUE ;
 DBUG_VOID_RETURN ;
 }
 do {
 if ( ( counter == 0 ) && do_read_query_result ( cn ) ) {
 cn -> pending = TRUE ;
 handle_error ( command , mysql_errno ( mysql ) , mysql_error ( mysql ) , mysql_sqlstate ( mysql ) , ds ) ;
 goto end ;
 }
 if ( mysql_field_count ( mysql ) && ( ( res = mysql_store_result ( mysql ) ) == 0 ) ) {
 handle_error ( command , mysql_errno ( mysql ) , mysql_error ( mysql ) , mysql_sqlstate ( mysql ) , ds ) ;
 goto end ;
 }
 if ( ! disable_result_log ) {
 if ( res ) {
 MYSQL_FIELD * fields = mysql_fetch_fields ( res ) ;
 uint num_fields = mysql_num_fields ( res ) ;
 if ( display_metadata ) append_metadata ( ds , fields , num_fields ) ;
 if ( ! display_result_vertically ) append_table_headings ( ds , fields , num_fields ) ;
 append_result ( ds , res ) ;
 }
 if ( ! disable_info ) append_info ( ds , mysql_affected_rows ( mysql ) , mysql_info ( mysql ) ) ;
 if ( ! disable_warnings && ! mysql_more_results ( mysql ) ) {
 if ( append_warnings ( ds_warnings , mysql ) || ds_warnings -> length ) {
 dynstr_append_mem ( ds , "Warnings:\n" , 10 ) ;
 dynstr_append_mem ( ds , ds_warnings -> str , ds_warnings -> length ) ;
 }
 }
 }
 if ( res ) {
 mysql_free_result ( res ) ;
 res = 0 ;
 }
 counter ++ ;
 }
 while ( ! ( err = mysql_next_result ( mysql ) ) ) ;
 if ( err > 0 ) {
 handle_error ( command , mysql_errno ( mysql ) , mysql_error ( mysql ) , mysql_sqlstate ( mysql ) , ds ) ;
 goto end ;
 }
 DBUG_ASSERT ( err == - 1 ) ;
 handle_no_error ( command ) ;
 revert_properties ( ) ;
 end : cn -> pending = FALSE ;
 var_set_errno ( mysql_errno ( mysql ) ) ;
 DBUG_VOID_RETURN ;
 }
void run_query_stmt ( struct st_connection * cn , struct st_command * command , char * query , int query_len , DYNAMIC_STRING * ds , DYNAMIC_STRING * ds_warnings ) {
 MYSQL_RES * res = NULL ;
 MYSQL * mysql = cn -> mysql ;
 MYSQL_STMT * stmt ;
 DYNAMIC_STRING ds_prepare_warnings ;
 DYNAMIC_STRING ds_execute_warnings ;
 DBUG_ENTER ( "run_query_stmt" ) ;
 DBUG_PRINT ( "query" , ( "'%-.60s'" , query ) ) ;
 if ( ! ( stmt = cn -> stmt ) ) {
 if ( ! ( stmt = mysql_stmt_init ( mysql ) ) ) die ( "unable to init stmt structure" ) ;
 cn -> stmt = stmt ;
 }
 if ( ! disable_warnings ) {
 init_dynamic_string ( & ds_prepare_warnings , NULL , 0 , 256 ) ;
 init_dynamic_string ( & ds_execute_warnings , NULL , 0 , 256 ) ;
 }
 if ( do_stmt_prepare ( cn , query , query_len ) ) {
 handle_error ( command , mysql_stmt_errno ( stmt ) , mysql_stmt_error ( stmt ) , mysql_stmt_sqlstate ( stmt ) , ds ) ;
 goto end ;
 }
 if ( ! disable_warnings ) append_warnings ( & ds_prepare_warnings , mysql ) ;

 ulong type = CURSOR_TYPE_READ_ONLY ;
 if ( mysql_stmt_attr_set ( stmt , STMT_ATTR_CURSOR_TYPE , ( void * ) & type ) ) die ( "mysql_stmt_attr_set(STMT_ATTR_CURSOR_TYPE) failed': %d %s" , mysql_stmt_errno ( stmt ) , mysql_stmt_error ( stmt ) ) ;
 }

 handle_error ( command , mysql_stmt_errno ( stmt ) , mysql_stmt_error ( stmt ) , mysql_stmt_sqlstate ( stmt ) , ds ) ;
 goto end ;
 }
 if ( cursor_protocol_enabled && ! disable_warnings ) append_warnings ( & ds_execute_warnings , mysql ) ;
 {
 my_bool one = 1 ;
 if ( mysql_stmt_attr_set ( stmt , STMT_ATTR_UPDATE_MAX_LENGTH , ( void * ) & one ) ) die ( "mysql_stmt_attr_set(STMT_ATTR_UPDATE_MAX_LENGTH) failed': %d %s" , mysql_stmt_errno ( stmt ) , mysql_stmt_error ( stmt ) ) ;
 }
 if ( mysql_stmt_field_count ( stmt ) && mysql_stmt_store_result ( stmt ) ) {
 handle_error ( command , mysql_stmt_errno ( stmt ) , mysql_stmt_error ( stmt ) , mysql_stmt_sqlstate ( stmt ) , ds ) ;
 goto end ;
 }
 handle_no_error ( command ) ;
 if ( ! disable_result_log ) {
 if ( ( res = mysql_stmt_result_metadata ( stmt ) ) != NULL ) {
 MYSQL_FIELD * fields = mysql_fetch_fields ( res ) ;
 uint num_fields = mysql_num_fields ( res ) ;
 if ( display_metadata ) append_metadata ( ds , fields , num_fields ) ;
 if ( ! display_result_vertically ) append_table_headings ( ds , fields , num_fields ) ;
 append_stmt_result ( ds , stmt , fields , num_fields ) ;
 mysql_free_result ( res ) ;
 if ( ! disable_warnings && ! prepare_warnings_enabled ) dynstr_set ( & ds_prepare_warnings , NULL ) ;
 }
 else {
 }
 if ( ! disable_info ) append_info ( ds , mysql_stmt_affected_rows ( stmt ) , mysql_info ( mysql ) ) ;
 if ( ! disable_warnings ) {
 if ( append_warnings ( & ds_execute_warnings , mysql ) || ds_execute_warnings . length || ds_prepare_warnings . length || ds_warnings -> length ) {
 dynstr_append_mem ( ds , "Warnings:\n" , 10 ) ;
 if ( ds_warnings -> length ) dynstr_append_mem ( ds , ds_warnings -> str , ds_warnings -> length ) ;
 if ( ds_prepare_warnings . length ) dynstr_append_mem ( ds , ds_prepare_warnings . str , ds_prepare_warnings . length ) ;
 if ( ds_execute_warnings . length ) dynstr_append_mem ( ds , ds_execute_warnings . str , ds_execute_warnings . length ) ;
 }
 }
 }
 end : if ( ! disable_warnings ) {
 dynstr_free ( & ds_prepare_warnings ) ;
 dynstr_free ( & ds_execute_warnings ) ;
 }
 var_set_errno ( mysql_stmt_errno ( stmt ) ) ;
 revert_properties ( ) ;
 if ( mysql -> reconnect ) {
 mysql_stmt_close ( stmt ) ;
 cn -> stmt = NULL ;
 }
 DBUG_VOID_RETURN ;
 }
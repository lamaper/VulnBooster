void run_query ( struct st_connection * cn , struct st_command * command , int flags ) {
 MYSQL * mysql = cn -> mysql ;
 DYNAMIC_STRING * ds ;
 DYNAMIC_STRING * save_ds = NULL ;
 DYNAMIC_STRING ds_result ;
 DYNAMIC_STRING ds_sorted ;
 DYNAMIC_STRING ds_warnings ;
 char * query ;
 int query_len ;
 my_bool view_created = 0 , sp_created = 0 ;
 my_bool complete_query = ( ( flags & QUERY_SEND_FLAG ) && ( flags & QUERY_REAP_FLAG ) ) ;
 DBUG_ENTER ( "run_query" ) ;
 if ( cn -> pending && ( flags & QUERY_SEND_FLAG ) ) die ( "Cannot run query on connection between send and reap" ) ;
 if ( ! ( flags & QUERY_SEND_FLAG ) && ! cn -> pending ) die ( "Cannot reap on a connection without pending send" ) ;
 init_dynamic_string ( & ds_warnings , NULL , 0 , 256 ) ;
 ds_warn = & ds_warnings ;
 if ( command -> type == Q_EVAL || command -> type == Q_SEND_EVAL ) {
 if ( ! command -> eval_query . str ) init_dynamic_string ( & command -> eval_query , "" , command -> query_len + 256 , 1024 ) ;
 else dynstr_set ( & command -> eval_query , 0 ) ;
 do_eval ( & command -> eval_query , command -> query , command -> end , FALSE ) ;
 query = command -> eval_query . str ;
 query_len = command -> eval_query . length ;
 }
 else {
 query = command -> query ;
 query_len = strlen ( query ) ;
 }
 if ( command -> require_file ) {
 init_dynamic_string ( & ds_result , "" , 1024 , 1024 ) ;
 ds = & ds_result ;
 }
 else ds = & ds_res ;
 if ( ! disable_query_log && ( flags & QUERY_SEND_FLAG ) ) {
 replace_dynstr_append_mem ( ds , query , query_len ) ;
 dynstr_append_mem ( ds , delimiter , delimiter_length ) ;
 dynstr_append_mem ( ds , "\n" , 1 ) ;
 }
 log_file . write ( & ds_res ) ;
 log_file . flush ( ) ;
 dynstr_set ( & ds_res , 0 ) ;
 if ( view_protocol_enabled && complete_query && match_re ( & view_re , query ) ) {
 DYNAMIC_STRING query_str ;
 init_dynamic_string ( & query_str , "CREATE OR REPLACE VIEW mysqltest_tmp_v AS " , query_len + 64 , 256 ) ;
 dynstr_append_mem ( & query_str , query , query_len ) ;
 if ( util_query ( mysql , query_str . str ) ) {
 DBUG_PRINT ( "view_create_error" , ( "Failed to create view '%s': %d: %s" , query_str . str , mysql_errno ( mysql ) , mysql_error ( mysql ) ) ) ;
 verbose_msg ( "Failed to create view '%s' %d: %s" , query_str . str , mysql_errno ( mysql ) , mysql_error ( mysql ) ) ;
 }
 else {
 view_created = 1 ;
 query = ( char * ) "SELECT * FROM mysqltest_tmp_v" ;
 query_len = strlen ( query ) ;
 append_warnings ( & ds_warnings , cur_con -> util_mysql ) ;
 }
 dynstr_free ( & query_str ) ;
 }
 if ( sp_protocol_enabled && complete_query && match_re ( & sp_re , query ) ) {
 DYNAMIC_STRING query_str ;
 init_dynamic_string ( & query_str , "DROP PROCEDURE IF EXISTS mysqltest_tmp_sp;
" , query_len + 64 , 256 ) ;
 util_query ( mysql , query_str . str ) ;
 dynstr_set ( & query_str , "CREATE PROCEDURE mysqltest_tmp_sp()\n" ) ;
 dynstr_append_mem ( & query_str , query , query_len ) ;
 if ( util_query ( mysql , query_str . str ) ) {
 DBUG_PRINT ( "sp_create_error" , ( "Failed to create sp '%s': %d: %s" , query_str . str , mysql_errno ( mysql ) , mysql_error ( mysql ) ) ) ;
 verbose_msg ( "Failed to create sp '%s' %d: %s" , query_str . str , mysql_errno ( mysql ) , mysql_error ( mysql ) ) ;
 }
 else {
 sp_created = 1 ;
 query = ( char * ) "CALL mysqltest_tmp_sp()" ;
 query_len = strlen ( query ) ;
 }
 dynstr_free ( & query_str ) ;
 }
 if ( display_result_sorted ) {
 init_dynamic_string ( & ds_sorted , "" , 1024 , 1024 ) ;
 save_ds = ds ;
 ds = & ds_sorted ;
 }
 if ( ps_protocol_enabled && complete_query && match_re ( & ps_re , query ) ) run_query_stmt ( cn , command , query , query_len , ds , & ds_warnings ) ;
 else run_query_normal ( cn , command , flags , query , query_len , ds , & ds_warnings ) ;
 dynstr_free ( & ds_warnings ) ;
 ds_warn = 0 ;
 if ( display_result_sorted ) {
 dynstr_append_sorted ( save_ds , & ds_sorted , 1 ) ;
 ds = save_ds ;
 dynstr_free ( & ds_sorted ) ;
 }
 if ( sp_created ) {
 if ( util_query ( mysql , "DROP PROCEDURE mysqltest_tmp_sp " ) ) report_or_die ( "Failed to drop sp: %d: %s" , mysql_errno ( mysql ) , mysql_error ( mysql ) ) ;
 }
 if ( view_created ) {
 if ( util_query ( mysql , "DROP VIEW mysqltest_tmp_v " ) ) report_or_die ( "Failed to drop view: %d: %s" , mysql_errno ( mysql ) , mysql_error ( mysql ) ) ;
 }
 if ( command -> require_file ) {
 check_require ( ds , command -> require_file ) ;
 }
 if ( ds == & ds_result ) dynstr_free ( & ds_result ) ;
 DBUG_VOID_RETURN ;
 }
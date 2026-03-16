bool mysql_routine_grant ( THD * thd , TABLE_LIST * table_list , bool is_proc , List < LEX_USER > & user_list , ulong rights , bool revoke_grant , bool write_to_binlog ) {
 List_iterator < LEX_USER > str_list ( user_list ) ;
 LEX_USER * Str , * tmp_Str ;
 TABLE_LIST tables [ 2 ] ;
 bool create_new_users = 0 , result = 0 ;
 char * db_name , * table_name ;
 bool save_binlog_row_based ;
 DBUG_ENTER ( "mysql_routine_grant" ) ;
 if ( ! initialized ) {
 my_error ( ER_OPTION_PREVENTS_STATEMENT , MYF ( 0 ) , "--skip-grant-tables" ) ;
 DBUG_RETURN ( TRUE ) ;
 }
 if ( rights & ~ PROC_ACLS ) {
 my_message ( ER_ILLEGAL_GRANT_FOR_TABLE , ER ( ER_ILLEGAL_GRANT_FOR_TABLE ) , MYF ( 0 ) ) ;
 DBUG_RETURN ( TRUE ) ;
 }
 if ( ! revoke_grant ) {
 if ( sp_exist_routines ( thd , table_list , is_proc ) ) DBUG_RETURN ( TRUE ) ;
 }
 bzero ( ( char * ) & tables , sizeof ( tables ) ) ;
 tables [ 0 ] . alias = tables [ 0 ] . table_name = ( char * ) "user" ;
 tables [ 1 ] . alias = tables [ 1 ] . table_name = ( char * ) "procs_priv" ;
 tables [ 0 ] . next_local = tables [ 0 ] . next_global = tables + 1 ;
 tables [ 0 ] . lock_type = tables [ 1 ] . lock_type = TL_WRITE ;
 tables [ 0 ] . db = tables [ 1 ] . db = ( char * ) "mysql" ;
 save_binlog_row_based = thd -> current_stmt_binlog_row_based ;
 thd -> clear_current_stmt_binlog_row_based ( ) ;

 tables [ 0 ] . updating = tables [ 1 ] . updating = 1 ;
 if ( ! ( thd -> spcont || rpl_filter -> tables_ok ( 0 , tables ) ) ) {
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( FALSE ) ;
 }
 }

 close_thread_tables ( thd ) ;
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( TRUE ) ;
 }
 if ( ! revoke_grant ) create_new_users = test_if_create_new_users ( thd ) ;
 rw_wrlock ( & LOCK_grant ) ;
 pthread_mutex_lock ( & acl_cache -> lock ) ;
 MEM_ROOT * old_root = thd -> mem_root ;
 thd -> mem_root = & memex ;
 DBUG_PRINT ( "info" , ( "now time to iterate and add users" ) ) ;
 while ( ( tmp_Str = str_list ++ ) ) {
 int error ;
 GRANT_NAME * grant_name ;
 if ( ! ( Str = get_current_user ( thd , tmp_Str ) ) ) {
 result = TRUE ;
 continue ;
 }
 error = replace_user_table ( thd , tables [ 0 ] . table , * Str , 0 , revoke_grant , create_new_users , test ( thd -> variables . sql_mode & MODE_NO_AUTO_CREATE_USER ) ) ;
 if ( error ) {
 result = TRUE ;
 continue ;
 }
 db_name = table_list -> db ;
 table_name = table_list -> table_name ;
 grant_name = routine_hash_search ( Str -> host . str , NullS , db_name , Str -> user . str , table_name , is_proc , 1 ) ;
 if ( ! grant_name ) {
 if ( revoke_grant ) {
 my_error ( ER_NONEXISTING_PROC_GRANT , MYF ( 0 ) , Str -> user . str , Str -> host . str , table_name ) ;
 result = TRUE ;
 continue ;
 }
 grant_name = new GRANT_NAME ( Str -> host . str , db_name , Str -> user . str , table_name , rights , TRUE ) ;
 if ( ! grant_name || my_hash_insert ( is_proc ? & proc_priv_hash : & func_priv_hash , ( uchar * ) grant_name ) ) {
 result = TRUE ;
 continue ;
 }
 }
 if ( replace_routine_table ( thd , grant_name , tables [ 1 ] . table , * Str , db_name , table_name , is_proc , rights , revoke_grant ) != 0 ) {
 result = TRUE ;
 continue ;
 }
 }
 thd -> mem_root = old_root ;
 pthread_mutex_unlock ( & acl_cache -> lock ) ;
 if ( write_to_binlog ) {
 if ( write_bin_log ( thd , FALSE , thd -> query ( ) , thd -> query_length ( ) ) ) result = TRUE ;
 }
 rw_unlock ( & LOCK_grant ) ;
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( result ) ;
 }
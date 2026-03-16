bool mysql_drop_user ( THD * thd , List < LEX_USER > & list ) {
 int result ;
 String wrong_users ;
 LEX_USER * user_name , * tmp_user_name ;
 List_iterator < LEX_USER > user_list ( list ) ;
 TABLE_LIST tables [ GRANT_TABLES ] ;
 bool some_users_deleted = FALSE ;
 ulong old_sql_mode = thd -> variables . sql_mode ;
 bool save_binlog_row_based ;
 DBUG_ENTER ( "mysql_drop_user" ) ;
 save_binlog_row_based = thd -> current_stmt_binlog_row_based ;
 thd -> clear_current_stmt_binlog_row_based ( ) ;
 if ( ( result = open_grant_tables ( thd , tables ) ) ) {
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( result != 1 ) ;
 }
 thd -> variables . sql_mode &= ~ MODE_PAD_CHAR_TO_FULL_LENGTH ;
 rw_wrlock ( & LOCK_grant ) ;
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 while ( ( tmp_user_name = user_list ++ ) ) {
 if ( ! ( user_name = get_current_user ( thd , tmp_user_name ) ) ) {
 result = TRUE ;
 continue ;
 }
 if ( handle_grant_data ( tables , 1 , user_name , NULL ) <= 0 ) {
 append_user ( & wrong_users , user_name ) ;
 result = TRUE ;
 continue ;
 }
 some_users_deleted = TRUE ;
 }
 rebuild_check_host ( ) ;
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 if ( result ) my_error ( ER_CANNOT_USER , MYF ( 0 ) , "DROP USER" , wrong_users . c_ptr_safe ( ) ) ;
 if ( some_users_deleted ) result |= write_bin_log ( thd , FALSE , thd -> query ( ) , thd -> query_length ( ) ) ;
 rw_unlock ( & LOCK_grant ) ;
 close_thread_tables ( thd ) ;
 thd -> variables . sql_mode = old_sql_mode ;
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( result ) ;
 }
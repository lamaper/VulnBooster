bool mysql_rename_user ( THD * thd , List < LEX_USER > & list ) {
 int result ;
 String wrong_users ;
 LEX_USER * user_from , * tmp_user_from ;
 LEX_USER * user_to , * tmp_user_to ;
 List_iterator < LEX_USER > user_list ( list ) ;
 TABLE_LIST tables [ GRANT_TABLES ] ;
 bool some_users_renamed = FALSE ;
 bool save_binlog_row_based ;
 DBUG_ENTER ( "mysql_rename_user" ) ;
 save_binlog_row_based = thd -> current_stmt_binlog_row_based ;
 thd -> clear_current_stmt_binlog_row_based ( ) ;
 if ( ( result = open_grant_tables ( thd , tables ) ) ) {
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( result != 1 ) ;
 }
 rw_wrlock ( & LOCK_grant ) ;
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 while ( ( tmp_user_from = user_list ++ ) ) {
 if ( ! ( user_from = get_current_user ( thd , tmp_user_from ) ) ) {
 result = TRUE ;
 continue ;
 }
 tmp_user_to = user_list ++ ;
 if ( ! ( user_to = get_current_user ( thd , tmp_user_to ) ) ) {
 result = TRUE ;
 continue ;
 }
 DBUG_ASSERT ( user_to != 0 ) ;
 if ( handle_grant_data ( tables , 0 , user_to , NULL ) || handle_grant_data ( tables , 0 , user_from , user_to ) <= 0 ) {
 append_user ( & wrong_users , user_from ) ;
 result = TRUE ;
 continue ;
 }
 some_users_renamed = TRUE ;
 }
 rebuild_check_host ( ) ;
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 if ( result ) my_error ( ER_CANNOT_USER , MYF ( 0 ) , "RENAME USER" , wrong_users . c_ptr_safe ( ) ) ;
 if ( some_users_renamed && mysql_bin_log . is_open ( ) ) result |= write_bin_log ( thd , FALSE , thd -> query ( ) , thd -> query_length ( ) ) ;
 rw_unlock ( & LOCK_grant ) ;
 close_thread_tables ( thd ) ;
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( result ) ;
 }
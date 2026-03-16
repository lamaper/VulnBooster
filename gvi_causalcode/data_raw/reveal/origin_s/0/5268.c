bool change_password ( THD * thd , const char * host , const char * user , char * new_password ) {
 TABLE_LIST tables ;
 TABLE * table ;
 char buff [ 512 ] ;
 ulong query_length ;
 bool save_binlog_row_based ;
 uint new_password_len = ( uint ) strlen ( new_password ) ;
 bool result = 1 ;
 DBUG_ENTER ( "change_password" ) ;
 DBUG_PRINT ( "enter" , ( "host: '%s' user: '%s' new_password: '%s'" , host , user , new_password ) ) ;
 DBUG_ASSERT ( host != 0 ) ;
 if ( check_change_password ( thd , host , user , new_password , new_password_len ) ) DBUG_RETURN ( 1 ) ;
 bzero ( ( char * ) & tables , sizeof ( tables ) ) ;
 tables . alias = tables . table_name = ( char * ) "user" ;
 tables . db = ( char * ) "mysql" ;

 tables . updating = 1 ;
 if ( ! ( thd -> spcont || rpl_filter -> tables_ok ( 0 , & tables ) ) ) DBUG_RETURN ( 0 ) ;
 }

 if ( ( save_binlog_row_based = thd -> current_stmt_binlog_row_based ) ) thd -> clear_current_stmt_binlog_row_based ( ) ;
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 ACL_USER * acl_user ;
 if ( ! ( acl_user = find_acl_user ( host , user , TRUE ) ) ) {
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 my_message ( ER_PASSWORD_NO_MATCH , ER ( ER_PASSWORD_NO_MATCH ) , MYF ( 0 ) ) ;
 goto end ;
 }
 set_user_salt ( acl_user , new_password , new_password_len ) ;
 if ( update_user_table ( thd , table , acl_user -> host . hostname ? acl_user -> host . hostname : "" , acl_user -> user ? acl_user -> user : "" , new_password , new_password_len ) ) {
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 goto end ;
 }
 acl_cache -> clear ( 1 ) ;
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 result = 0 ;
 if ( mysql_bin_log . is_open ( ) ) {
 query_length = sprintf ( buff , "SET PASSWORD FOR '%-.120s'@'%-.120s'='%-.120s'" , acl_user -> user ? acl_user -> user : "" , acl_user -> host . hostname ? acl_user -> host . hostname : "" , new_password ) ;
 thd -> clear_error ( ) ;
 result = thd -> binlog_query ( THD : : MYSQL_QUERY_TYPE , buff , query_length , FALSE , FALSE , 0 ) ;
 }
 end : close_thread_tables ( thd ) ;
 DBUG_ASSERT ( ! thd -> current_stmt_binlog_row_based ) ;
 if ( save_binlog_row_based ) thd -> set_current_stmt_binlog_row_based ( ) ;
 DBUG_RETURN ( result ) ;
 }
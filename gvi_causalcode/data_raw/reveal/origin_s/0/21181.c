bool mysql_grant ( THD * thd , const char * db , List < LEX_USER > & list , ulong rights , bool revoke_grant ) {
 List_iterator < LEX_USER > str_list ( list ) ;
 LEX_USER * Str , * tmp_Str ;
 char tmp_db [ NAME_LEN + 1 ] ;
 bool create_new_users = 0 ;
 TABLE_LIST tables [ 2 ] ;
 bool save_binlog_row_based ;
 DBUG_ENTER ( "mysql_grant" ) ;
 if ( ! initialized ) {
 my_error ( ER_OPTION_PREVENTS_STATEMENT , MYF ( 0 ) , "--skip-grant-tables" ) ;
 DBUG_RETURN ( TRUE ) ;
 }
 if ( lower_case_table_names && db ) {
 strnmov ( tmp_db , db , NAME_LEN ) ;
 tmp_db [ NAME_LEN ] = '\0' ;
 my_casedn_str ( files_charset_info , tmp_db ) ;
 db = tmp_db ;
 }
 bzero ( ( char * ) & tables , sizeof ( tables ) ) ;
 tables [ 0 ] . alias = tables [ 0 ] . table_name = ( char * ) "user" ;
 tables [ 1 ] . alias = tables [ 1 ] . table_name = ( char * ) "db" ;
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
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 grant_version ++ ;
 int result = 0 ;
 while ( ( tmp_Str = str_list ++ ) ) {
 if ( ! ( Str = get_current_user ( thd , tmp_Str ) ) ) {
 result = TRUE ;
 continue ;
 }
 if ( ! tmp_Str -> user . str && tmp_Str -> password . str ) Str -> password = tmp_Str -> password ;
 if ( replace_user_table ( thd , tables [ 0 ] . table , * Str , ( ! db ? rights : 0 ) , revoke_grant , create_new_users , test ( thd -> variables . sql_mode & MODE_NO_AUTO_CREATE_USER ) ) ) result = - 1 ;
 else if ( db ) {
 ulong db_rights = rights & DB_ACLS ;
 if ( db_rights == rights ) {
 if ( replace_db_table ( tables [ 1 ] . table , db , * Str , db_rights , revoke_grant ) ) result = - 1 ;
 }
 else {
 my_error ( ER_WRONG_USAGE , MYF ( 0 ) , "DB GRANT" , "GLOBAL PRIVILEGES" ) ;
 result = - 1 ;
 }
 }
 }
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 if ( ! result ) {
 result = write_bin_log ( thd , TRUE , thd -> query ( ) , thd -> query_length ( ) ) ;
 }
 rw_unlock ( & LOCK_grant ) ;
 close_thread_tables ( thd ) ;
 if ( ! result ) my_ok ( thd ) ;
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( result ) ;
 }
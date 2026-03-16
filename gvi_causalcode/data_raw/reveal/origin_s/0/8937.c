int mysql_table_grant ( THD * thd , TABLE_LIST * table_list , List < LEX_USER > & user_list , List < LEX_COLUMN > & columns , ulong rights , bool revoke_grant ) {
 ulong column_priv = 0 ;
 List_iterator < LEX_USER > str_list ( user_list ) ;
 LEX_USER * Str , * tmp_Str ;
 TABLE_LIST tables [ 3 ] ;
 bool create_new_users = 0 ;
 char * db_name , * table_name ;
 bool save_binlog_row_based ;
 DBUG_ENTER ( "mysql_table_grant" ) ;
 if ( ! initialized ) {
 my_error ( ER_OPTION_PREVENTS_STATEMENT , MYF ( 0 ) , "--skip-grant-tables" ) ;
 DBUG_RETURN ( TRUE ) ;
 }
 if ( rights & ~ TABLE_ACLS ) {
 my_message ( ER_ILLEGAL_GRANT_FOR_TABLE , ER ( ER_ILLEGAL_GRANT_FOR_TABLE ) , MYF ( 0 ) ) ;
 DBUG_RETURN ( TRUE ) ;
 }
 if ( ! revoke_grant ) {
 if ( columns . elements ) {
 class LEX_COLUMN * column ;
 List_iterator < LEX_COLUMN > column_iter ( columns ) ;
 if ( open_and_lock_tables ( thd , table_list ) ) DBUG_RETURN ( TRUE ) ;
 while ( ( column = column_iter ++ ) ) {
 uint unused_field_idx = NO_CACHED_FIELD_INDEX ;
 TABLE_LIST * dummy ;
 Field * f = find_field_in_table_ref ( thd , table_list , column -> column . ptr ( ) , column -> column . length ( ) , column -> column . ptr ( ) , NULL , NULL , NULL , TRUE , FALSE , & unused_field_idx , FALSE , & dummy ) ;
 if ( f == ( Field * ) 0 ) {
 my_error ( ER_BAD_FIELD_ERROR , MYF ( 0 ) , column -> column . c_ptr ( ) , table_list -> alias ) ;
 DBUG_RETURN ( TRUE ) ;
 }
 if ( f == ( Field * ) - 1 ) DBUG_RETURN ( TRUE ) ;
 column_priv |= column -> rights ;
 }
 close_thread_tables ( thd ) ;
 }
 else {
 if ( ! ( rights & CREATE_ACL ) ) {
 char buf [ FN_REFLEN + 1 ] ;
 build_table_filename ( buf , sizeof ( buf ) - 1 , table_list -> db , table_list -> table_name , reg_ext , 0 ) ;
 fn_format ( buf , buf , "" , "" , MY_UNPACK_FILENAME | MY_RESOLVE_SYMLINKS | MY_RETURN_REAL_PATH | MY_APPEND_EXT ) ;
 if ( access ( buf , F_OK ) ) {
 my_error ( ER_NO_SUCH_TABLE , MYF ( 0 ) , table_list -> db , table_list -> alias ) ;
 DBUG_RETURN ( TRUE ) ;
 }
 }
 if ( table_list -> grant . want_privilege ) {
 char command [ 128 ] ;
 get_privilege_desc ( command , sizeof ( command ) , table_list -> grant . want_privilege ) ;
 my_error ( ER_TABLEACCESS_DENIED_ERROR , MYF ( 0 ) , command , thd -> security_ctx -> priv_user , thd -> security_ctx -> host_or_ip , table_list -> alias ) ;
 DBUG_RETURN ( - 1 ) ;
 }
 }
 }
 bzero ( ( char * ) & tables , sizeof ( tables ) ) ;
 tables [ 0 ] . alias = tables [ 0 ] . table_name = ( char * ) "user" ;
 tables [ 1 ] . alias = tables [ 1 ] . table_name = ( char * ) "tables_priv" ;
 tables [ 2 ] . alias = tables [ 2 ] . table_name = ( char * ) "columns_priv" ;
 tables [ 0 ] . next_local = tables [ 0 ] . next_global = tables + 1 ;
 tables [ 1 ] . next_local = tables [ 1 ] . next_global = ( ( column_priv || ( revoke_grant && ( ( rights & COL_ACLS ) || columns . elements ) ) ) ? tables + 2 : 0 ) ;
 tables [ 0 ] . lock_type = tables [ 1 ] . lock_type = tables [ 2 ] . lock_type = TL_WRITE ;
 tables [ 0 ] . db = tables [ 1 ] . db = tables [ 2 ] . db = ( char * ) "mysql" ;
 save_binlog_row_based = thd -> current_stmt_binlog_row_based ;
 thd -> clear_current_stmt_binlog_row_based ( ) ;

 tables [ 0 ] . updating = tables [ 1 ] . updating = tables [ 2 ] . updating = 1 ;
 if ( ! ( thd -> spcont || rpl_filter -> tables_ok ( 0 , tables ) ) ) {
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( FALSE ) ;
 }
 }

 thd -> lex -> reset_n_backup_query_tables_list ( & backup ) ;
 if ( simple_open_n_lock_tables ( thd , tables ) ) {
 close_thread_tables ( thd ) ;
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( TRUE ) ;
 }
 if ( ! revoke_grant ) create_new_users = test_if_create_new_users ( thd ) ;
 bool result = FALSE ;
 rw_wrlock ( & LOCK_grant ) ;
 pthread_mutex_lock ( & acl_cache -> lock ) ;
 MEM_ROOT * old_root = thd -> mem_root ;
 thd -> mem_root = & memex ;
 grant_version ++ ;
 while ( ( tmp_Str = str_list ++ ) ) {
 int error ;
 GRANT_TABLE * grant_table ;
 if ( ! ( Str = get_current_user ( thd , tmp_Str ) ) ) {
 result = TRUE ;
 continue ;
 }
 error = replace_user_table ( thd , tables [ 0 ] . table , * Str , 0 , revoke_grant , create_new_users , test ( thd -> variables . sql_mode & MODE_NO_AUTO_CREATE_USER ) ) ;
 if ( error ) {
 result = TRUE ;
 continue ;
 }
 db_name = table_list -> get_db_name ( ) ;
 table_name = table_list -> get_table_name ( ) ;
 grant_table = table_hash_search ( Str -> host . str , NullS , db_name , Str -> user . str , table_name , 1 ) ;
 if ( ! grant_table ) {
 if ( revoke_grant ) {
 my_error ( ER_NONEXISTING_TABLE_GRANT , MYF ( 0 ) , Str -> user . str , Str -> host . str , table_list -> table_name ) ;
 result = TRUE ;
 continue ;
 }
 grant_table = new GRANT_TABLE ( Str -> host . str , db_name , Str -> user . str , table_name , rights , column_priv ) ;
 if ( ! grant_table || my_hash_insert ( & column_priv_hash , ( uchar * ) grant_table ) ) {
 result = TRUE ;
 continue ;
 }
 }
 if ( revoke_grant ) {
 class LEX_COLUMN * column ;
 List_iterator < LEX_COLUMN > column_iter ( columns ) ;
 GRANT_COLUMN * grant_column ;
 while ( ( column = column_iter ++ ) ) {
 grant_column = column_hash_search ( grant_table , column -> column . ptr ( ) , column -> column . length ( ) ) ;
 if ( grant_column ) grant_column -> rights &= ~ ( column -> rights | rights ) ;
 }
 column_priv = 0 ;
 for ( uint idx = 0 ;
 idx < grant_table -> hash_columns . records ;
 idx ++ ) {
 grant_column = ( GRANT_COLUMN * ) hash_element ( & grant_table -> hash_columns , idx ) ;
 grant_column -> rights &= ~ rights ;
 column_priv |= grant_column -> rights ;
 }
 }
 else {
 column_priv |= grant_table -> cols ;
 }
 if ( replace_table_table ( thd , grant_table , tables [ 1 ] . table , * Str , db_name , table_name , rights , column_priv , revoke_grant ) ) {
 result = TRUE ;
 }
 else if ( tables [ 2 ] . table ) {
 if ( ( replace_column_table ( grant_table , tables [ 2 ] . table , * Str , columns , db_name , table_name , rights , revoke_grant ) ) ) {
 result = TRUE ;
 }
 }
 }
 thd -> mem_root = old_root ;
 pthread_mutex_unlock ( & acl_cache -> lock ) ;
 if ( ! result ) {
 result = write_bin_log ( thd , TRUE , thd -> query ( ) , thd -> query_length ( ) ) ;
 }
 rw_unlock ( & LOCK_grant ) ;
 if ( ! result ) my_ok ( thd ) ;
 thd -> lex -> restore_backup_query_tables_list ( & backup ) ;
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( result ) ;
 }
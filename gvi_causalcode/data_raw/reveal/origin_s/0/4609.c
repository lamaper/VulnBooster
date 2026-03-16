bool sp_revoke_privileges ( THD * thd , const char * sp_db , const char * sp_name , bool is_proc ) {
 uint counter , revoked ;
 int result ;
 TABLE_LIST tables [ GRANT_TABLES ] ;
 HASH * hash = is_proc ? & proc_priv_hash : & func_priv_hash ;
 Silence_routine_definer_errors error_handler ;
 bool save_binlog_row_based ;
 DBUG_ENTER ( "sp_revoke_privileges" ) ;
 if ( ( result = open_grant_tables ( thd , tables ) ) ) DBUG_RETURN ( result != 1 ) ;
 thd -> push_internal_handler ( & error_handler ) ;
 rw_wrlock ( & LOCK_grant ) ;
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 save_binlog_row_based = thd -> current_stmt_binlog_row_based ;
 thd -> clear_current_stmt_binlog_row_based ( ) ;
 do {
 for ( counter = 0 , revoked = 0 ;
 counter < hash -> records ;
 ) {
 GRANT_NAME * grant_proc = ( GRANT_NAME * ) hash_element ( hash , counter ) ;
 if ( ! my_strcasecmp ( & my_charset_utf8_bin , grant_proc -> db , sp_db ) && ! my_strcasecmp ( system_charset_info , grant_proc -> tname , sp_name ) ) {
 LEX_USER lex_user ;
 lex_user . user . str = grant_proc -> user ;
 lex_user . user . length = strlen ( grant_proc -> user ) ;
 lex_user . host . str = grant_proc -> host . hostname ? grant_proc -> host . hostname : ( char * ) "" ;
 lex_user . host . length = grant_proc -> host . hostname ? strlen ( grant_proc -> host . hostname ) : 0 ;
 if ( replace_routine_table ( thd , grant_proc , tables [ 4 ] . table , lex_user , grant_proc -> db , grant_proc -> tname , is_proc , ~ ( ulong ) 0 , 1 ) == 0 ) {
 revoked = 1 ;
 continue ;
 }
 }
 counter ++ ;
 }
 }
 while ( revoked ) ;
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 rw_unlock ( & LOCK_grant ) ;
 close_thread_tables ( thd ) ;
 thd -> pop_internal_handler ( ) ;
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( error_handler . has_errors ( ) ) ;
 }
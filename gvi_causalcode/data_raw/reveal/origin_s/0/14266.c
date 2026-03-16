bool mysql_revoke_all ( THD * thd , List < LEX_USER > & list ) {
 uint counter , revoked , is_proc ;
 int result ;
 ACL_DB * acl_db ;
 TABLE_LIST tables [ GRANT_TABLES ] ;
 bool save_binlog_row_based ;
 DBUG_ENTER ( "mysql_revoke_all" ) ;
 save_binlog_row_based = thd -> current_stmt_binlog_row_based ;
 thd -> clear_current_stmt_binlog_row_based ( ) ;
 if ( ( result = open_grant_tables ( thd , tables ) ) ) {
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( result != 1 ) ;
 }
 rw_wrlock ( & LOCK_grant ) ;
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 LEX_USER * lex_user , * tmp_lex_user ;
 List_iterator < LEX_USER > user_list ( list ) ;
 while ( ( tmp_lex_user = user_list ++ ) ) {
 if ( ! ( lex_user = get_current_user ( thd , tmp_lex_user ) ) ) {
 result = - 1 ;
 continue ;
 }
 if ( ! find_acl_user ( lex_user -> host . str , lex_user -> user . str , TRUE ) ) {
 result = - 1 ;
 continue ;
 }
 if ( replace_user_table ( thd , tables [ 0 ] . table , * lex_user , ~ ( ulong ) 0 , 1 , 0 , 0 ) ) {
 result = - 1 ;
 continue ;
 }
 do {
 for ( counter = 0 , revoked = 0 ;
 counter < acl_dbs . elements ;
 ) {
 const char * user , * host ;
 acl_db = dynamic_element ( & acl_dbs , counter , ACL_DB * ) ;
 if ( ! ( user = acl_db -> user ) ) user = "" ;
 if ( ! ( host = acl_db -> host . hostname ) ) host = "" ;
 if ( ! strcmp ( lex_user -> user . str , user ) && ! strcmp ( lex_user -> host . str , host ) ) {
 if ( ! replace_db_table ( tables [ 1 ] . table , acl_db -> db , * lex_user , ~ ( ulong ) 0 , 1 ) ) {
 revoked = 1 ;
 continue ;
 }
 result = - 1 ;
 }
 counter ++ ;
 }
 }
 while ( revoked ) ;
 do {
 for ( counter = 0 , revoked = 0 ;
 counter < column_priv_hash . records ;
 ) {
 const char * user , * host ;
 GRANT_TABLE * grant_table = ( GRANT_TABLE * ) hash_element ( & column_priv_hash , counter ) ;
 if ( ! ( user = grant_table -> user ) ) user = "" ;
 if ( ! ( host = grant_table -> host . hostname ) ) host = "" ;
 if ( ! strcmp ( lex_user -> user . str , user ) && ! strcmp ( lex_user -> host . str , host ) ) {
 if ( replace_table_table ( thd , grant_table , tables [ 2 ] . table , * lex_user , grant_table -> db , grant_table -> tname , ~ ( ulong ) 0 , 0 , 1 ) ) {
 result = - 1 ;
 }
 else {
 if ( ! grant_table -> cols ) {
 revoked = 1 ;
 continue ;
 }
 List < LEX_COLUMN > columns ;
 if ( ! replace_column_table ( grant_table , tables [ 3 ] . table , * lex_user , columns , grant_table -> db , grant_table -> tname , ~ ( ulong ) 0 , 1 ) ) {
 revoked = 1 ;
 continue ;
 }
 result = - 1 ;
 }
 }
 counter ++ ;
 }
 }
 while ( revoked ) ;
 for ( is_proc = 0 ;
 is_proc < 2 ;
 is_proc ++ ) do {
 HASH * hash = is_proc ? & proc_priv_hash : & func_priv_hash ;
 for ( counter = 0 , revoked = 0 ;
 counter < hash -> records ;
 ) {
 const char * user , * host ;
 GRANT_NAME * grant_proc = ( GRANT_NAME * ) hash_element ( hash , counter ) ;
 if ( ! ( user = grant_proc -> user ) ) user = "" ;
 if ( ! ( host = grant_proc -> host . hostname ) ) host = "" ;
 if ( ! strcmp ( lex_user -> user . str , user ) && ! strcmp ( lex_user -> host . str , host ) ) {
 if ( replace_routine_table ( thd , grant_proc , tables [ 4 ] . table , * lex_user , grant_proc -> db , grant_proc -> tname , is_proc , ~ ( ulong ) 0 , 1 ) == 0 ) {
 revoked = 1 ;
 continue ;
 }
 result = - 1 ;
 }
 counter ++ ;
 }
 }
 while ( revoked ) ;
 }
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 if ( result ) my_message ( ER_REVOKE_GRANTS , ER ( ER_REVOKE_GRANTS ) , MYF ( 0 ) ) ;
 result = result | write_bin_log ( thd , FALSE , thd -> query ( ) , thd -> query_length ( ) ) ;
 rw_unlock ( & LOCK_grant ) ;
 close_thread_tables ( thd ) ;
 thd -> current_stmt_binlog_row_based = save_binlog_row_based ;
 DBUG_RETURN ( result ) ;
 }
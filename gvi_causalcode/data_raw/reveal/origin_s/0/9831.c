bool check_column_grant_in_table_ref ( THD * thd , TABLE_LIST * table_ref , const char * name , uint length ) {
 GRANT_INFO * grant ;
 const char * db_name ;
 const char * table_name ;
 Security_context * sctx = test ( table_ref -> security_ctx ) ? table_ref -> security_ctx : thd -> security_ctx ;
 if ( table_ref -> view || table_ref -> field_translation ) {
 ulong view_privs ;
 grant = & ( table_ref -> grant ) ;
 db_name = table_ref -> view_db . str ;
 table_name = table_ref -> view_name . str ;
 if ( table_ref -> belong_to_view && thd -> lex -> sql_command == SQLCOM_SHOW_FIELDS ) {
 view_privs = get_column_grant ( thd , grant , db_name , table_name , name ) ;
 if ( view_privs & VIEW_ANY_ACL ) {
 table_ref -> belong_to_view -> allowed_show = TRUE ;
 return FALSE ;
 }
 table_ref -> belong_to_view -> allowed_show = FALSE ;
 my_message ( ER_VIEW_NO_EXPLAIN , ER ( ER_VIEW_NO_EXPLAIN ) , MYF ( 0 ) ) ;
 return TRUE ;
 }
 }
 else {
 TABLE * table = table_ref -> table ;
 grant = & ( table -> grant ) ;
 db_name = table -> s -> db . str ;
 table_name = table -> s -> table_name . str ;
 }
 if ( grant -> want_privilege ) return check_grant_column ( thd , grant , db_name , table_name , name , length , sctx ) ;
 else return FALSE ;
 }
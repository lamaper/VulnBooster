static bool check_grant_db_routine ( THD * thd , const char * db , HASH * hash ) {
 Security_context * sctx = thd -> security_ctx ;
 for ( uint idx = 0 ;
 idx < hash -> records ;
 ++ idx ) {
 GRANT_NAME * item = ( GRANT_NAME * ) hash_element ( hash , idx ) ;
 if ( strcmp ( item -> user , sctx -> priv_user ) == 0 && strcmp ( item -> db , db ) == 0 && compare_hostname ( & item -> host , sctx -> host , sctx -> ip ) ) {
 return FALSE ;
 }
 }
 return TRUE ;
 }
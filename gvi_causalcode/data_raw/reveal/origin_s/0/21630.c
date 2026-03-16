bool check_grant_db ( THD * thd , const char * db ) {
 Security_context * sctx = thd -> security_ctx ;
 char helping [ NAME_LEN + USERNAME_LENGTH + 2 ] ;
 uint len ;
 bool error = TRUE ;
 size_t copy_length ;
 copy_length = ( size_t ) ( strlen ( sctx -> priv_user ? sctx -> priv_user : "" ) + strlen ( db ? db : "" ) ) + 1 ;
 if ( copy_length >= ( NAME_LEN + USERNAME_LENGTH + 2 ) ) return 1 ;
 len = ( uint ) ( strmov ( strmov ( helping , sctx -> priv_user ) + 1 , db ) - helping ) + 1 ;
 rw_rdlock ( & LOCK_grant ) ;
 for ( uint idx = 0 ;
 idx < column_priv_hash . records ;
 idx ++ ) {
 GRANT_TABLE * grant_table = ( GRANT_TABLE * ) hash_element ( & column_priv_hash , idx ) ;
 if ( len < grant_table -> key_length && ! memcmp ( grant_table -> hash_key , helping , len ) && compare_hostname ( & grant_table -> host , sctx -> host , sctx -> ip ) ) {
 error = FALSE ;
 break ;
 }
 }
 if ( error ) error = check_grant_db_routine ( thd , db , & proc_priv_hash ) && check_grant_db_routine ( thd , db , & func_priv_hash ) ;
 rw_unlock ( & LOCK_grant ) ;
 return error ;
 }
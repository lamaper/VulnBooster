bool check_routine_level_acl ( THD * thd , const char * db , const char * name , bool is_proc ) {
 bool no_routine_acl = 1 ;
 GRANT_NAME * grant_proc ;
 Security_context * sctx = thd -> security_ctx ;
 rw_rdlock ( & LOCK_grant ) ;
 if ( ( grant_proc = routine_hash_search ( sctx -> priv_host , sctx -> ip , db , sctx -> priv_user , name , is_proc , 0 ) ) ) no_routine_acl = ! ( grant_proc -> privs & SHOW_PROC_ACLS ) ;
 rw_unlock ( & LOCK_grant ) ;
 return no_routine_acl ;
 }
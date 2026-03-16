void fill_effective_table_privileges ( THD * thd , GRANT_INFO * grant , const char * db , const char * table ) {
 Security_context * sctx = thd -> security_ctx ;
 DBUG_ENTER ( "fill_effective_table_privileges" ) ;
 DBUG_PRINT ( "enter" , ( "Host: '%s', Ip: '%s', User: '%s', table: `%s`.`%s`" , sctx -> priv_host , ( sctx -> ip ? sctx -> ip : "(NULL)" ) , ( sctx -> priv_user ? sctx -> priv_user : "(NULL)" ) , db , table ) ) ;
 if ( ! initialized ) {
 DBUG_PRINT ( "info" , ( "skip grants" ) ) ;
 grant -> privilege = ~ NO_ACCESS ;
 DBUG_PRINT ( "info" , ( "privilege 0x%lx" , grant -> privilege ) ) ;
 DBUG_VOID_RETURN ;
 }
 grant -> privilege = sctx -> master_access ;
 if ( ! sctx -> priv_user ) {
 DBUG_PRINT ( "info" , ( "privilege 0x%lx" , grant -> privilege ) ) ;
 DBUG_VOID_RETURN ;
 }
 grant -> privilege |= acl_get ( sctx -> host , sctx -> ip , sctx -> priv_user , db , 0 ) ;
 rw_rdlock ( & LOCK_grant ) ;
 if ( grant -> version != grant_version ) {
 grant -> grant_table = table_hash_search ( sctx -> host , sctx -> ip , db , sctx -> priv_user , table , 0 ) ;
 grant -> version = grant_version ;
 }
 if ( grant -> grant_table != 0 ) {
 grant -> privilege |= grant -> grant_table -> privs ;
 }
 rw_unlock ( & LOCK_grant ) ;
 DBUG_PRINT ( "info" , ( "privilege 0x%lx" , grant -> privilege ) ) ;
 DBUG_VOID_RETURN ;
 }
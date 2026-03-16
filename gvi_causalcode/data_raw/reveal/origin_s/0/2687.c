ulong get_column_grant ( THD * thd , GRANT_INFO * grant , const char * db_name , const char * table_name , const char * field_name ) {
 GRANT_TABLE * grant_table ;
 GRANT_COLUMN * grant_column ;
 ulong priv ;
 rw_rdlock ( & LOCK_grant ) ;
 if ( grant -> version != grant_version ) {
 Security_context * sctx = thd -> security_ctx ;
 grant -> grant_table = table_hash_search ( sctx -> host , sctx -> ip , db_name , sctx -> priv_user , table_name , 0 ) ;
 grant -> version = grant_version ;
 }
 if ( ! ( grant_table = grant -> grant_table ) ) priv = grant -> privilege ;
 else {
 grant_column = column_hash_search ( grant_table , field_name , ( uint ) strlen ( field_name ) ) ;
 if ( ! grant_column ) priv = ( grant -> privilege | grant_table -> privs ) ;
 else priv = ( grant -> privilege | grant_table -> privs | grant_column -> rights ) ;
 }
 rw_unlock ( & LOCK_grant ) ;
 return priv ;
 }
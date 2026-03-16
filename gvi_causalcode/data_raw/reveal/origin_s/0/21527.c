bool check_grant_column ( THD * thd , GRANT_INFO * grant , const char * db_name , const char * table_name , const char * name , uint length , Security_context * sctx ) {
 GRANT_TABLE * grant_table ;
 GRANT_COLUMN * grant_column ;
 ulong want_access = grant -> want_privilege & ~ grant -> privilege ;
 DBUG_ENTER ( "check_grant_column" ) ;
 DBUG_PRINT ( "enter" , ( "table: %s want_access: %lu" , table_name , want_access ) ) ;
 if ( ! want_access ) DBUG_RETURN ( 0 ) ;
 rw_rdlock ( & LOCK_grant ) ;
 if ( grant -> version != grant_version ) {
 grant -> grant_table = table_hash_search ( sctx -> host , sctx -> ip , db_name , sctx -> priv_user , table_name , 0 ) ;
 grant -> version = grant_version ;
 }
 if ( ! ( grant_table = grant -> grant_table ) ) goto err ;
 grant_column = column_hash_search ( grant_table , name , length ) ;
 if ( grant_column && ! ( ~ grant_column -> rights & want_access ) ) {
 rw_unlock ( & LOCK_grant ) ;
 DBUG_RETURN ( 0 ) ;
 }
 err : rw_unlock ( & LOCK_grant ) ;
 char command [ 128 ] ;
 get_privilege_desc ( command , sizeof ( command ) , want_access ) ;
 my_error ( ER_COLUMNACCESS_DENIED_ERROR , MYF ( 0 ) , command , sctx -> priv_user , sctx -> host_or_ip , name , table_name ) ;
 DBUG_RETURN ( 1 ) ;
 }
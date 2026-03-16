int fill_schema_table_privileges ( THD * thd , TABLE_LIST * tables , COND * cond ) {

 uint index ;
 char buff [ 100 ] ;
 TABLE * table = tables -> table ;
 bool no_global_access = check_access ( thd , SELECT_ACL , "mysql" , 0 , 1 , 1 , 0 ) ;
 char * curr_host = thd -> security_ctx -> priv_host_name ( ) ;
 DBUG_ENTER ( "fill_schema_table_privileges" ) ;
 rw_rdlock ( & LOCK_grant ) ;
 for ( index = 0 ;
 index < column_priv_hash . records ;
 index ++ ) {
 const char * user , * host , * is_grantable = "YES" ;
 GRANT_TABLE * grant_table = ( GRANT_TABLE * ) hash_element ( & column_priv_hash , index ) ;
 if ( ! ( user = grant_table -> user ) ) user = "" ;
 if ( ! ( host = grant_table -> host . hostname ) ) host = "" ;
 if ( no_global_access && ( strcmp ( thd -> security_ctx -> priv_user , user ) || my_strcasecmp ( system_charset_info , curr_host , host ) ) ) continue ;
 ulong table_access = grant_table -> privs ;
 if ( table_access ) {
 ulong test_access = table_access & ~ GRANT_ACL ;
 if ( ! test_access && grant_table -> cols ) continue ;
 if ( ! ( table_access & GRANT_ACL ) ) is_grantable = "NO" ;
 strxmov ( buff , "'" , user , "'@'" , host , "'" , NullS ) ;
 if ( ! test_access ) {
 if ( update_schema_privilege ( thd , table , buff , grant_table -> db , grant_table -> tname , 0 , 0 , STRING_WITH_LEN ( "USAGE" ) , is_grantable ) ) {
 error = 1 ;
 goto err ;
 }
 }
 else {
 ulong j ;
 int cnt ;
 for ( cnt = 0 , j = SELECT_ACL ;
 j <= TABLE_ACLS ;
 cnt ++ , j <<= 1 ) {
 if ( test_access & j ) {
 if ( update_schema_privilege ( thd , table , buff , grant_table -> db , grant_table -> tname , 0 , 0 , command_array [ cnt ] , command_lengths [ cnt ] , is_grantable ) ) {
 error = 1 ;
 goto err ;
 }
 }
 }
 }
 }
 }
 err : rw_unlock ( & LOCK_grant ) ;
 DBUG_RETURN ( error ) ;


int fill_schema_schema_privileges ( THD * thd , TABLE_LIST * tables , COND * cond ) {

 uint counter ;
 ACL_DB * acl_db ;
 ulong want_access ;
 char buff [ 100 ] ;
 TABLE * table = tables -> table ;
 bool no_global_access = check_access ( thd , SELECT_ACL , "mysql" , 0 , 1 , 1 , 0 ) ;
 char * curr_host = thd -> security_ctx -> priv_host_name ( ) ;
 DBUG_ENTER ( "fill_schema_schema_privileges" ) ;
 if ( ! initialized ) DBUG_RETURN ( 0 ) ;
 pthread_mutex_lock ( & acl_cache -> lock ) ;
 for ( counter = 0 ;
 counter < acl_dbs . elements ;
 counter ++ ) {
 const char * user , * host , * is_grantable = "YES" ;
 acl_db = dynamic_element ( & acl_dbs , counter , ACL_DB * ) ;
 if ( ! ( user = acl_db -> user ) ) user = "" ;
 if ( ! ( host = acl_db -> host . hostname ) ) host = "" ;
 if ( no_global_access && ( strcmp ( thd -> security_ctx -> priv_user , user ) || my_strcasecmp ( system_charset_info , curr_host , host ) ) ) continue ;
 want_access = acl_db -> access ;
 if ( want_access ) {
 if ( ! ( want_access & GRANT_ACL ) ) {
 is_grantable = "NO" ;
 }
 strxmov ( buff , "'" , user , "'@'" , host , "'" , NullS ) ;
 if ( ! ( want_access & ~ GRANT_ACL ) ) {
 if ( update_schema_privilege ( thd , table , buff , acl_db -> db , 0 , 0 , 0 , STRING_WITH_LEN ( "USAGE" ) , is_grantable ) ) {
 error = 1 ;
 goto err ;
 }
 }
 else {
 int cnt ;
 ulong j , test_access = want_access & ~ GRANT_ACL ;
 for ( cnt = 0 , j = SELECT_ACL ;
 j <= DB_ACLS ;
 cnt ++ , j <<= 1 ) if ( test_access & j ) {
 if ( update_schema_privilege ( thd , table , buff , acl_db -> db , 0 , 0 , 0 , command_array [ cnt ] , command_lengths [ cnt ] , is_grantable ) ) {
 error = 1 ;
 goto err ;
 }
 }
 }
 }
 }
 err : pthread_mutex_unlock ( & acl_cache -> lock ) ;
 DBUG_RETURN ( error ) ;


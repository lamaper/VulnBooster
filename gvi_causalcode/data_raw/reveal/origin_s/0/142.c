int fill_schema_user_privileges ( THD * thd , TABLE_LIST * tables , COND * cond ) {

 uint counter ;
 ACL_USER * acl_user ;
 ulong want_access ;
 char buff [ 100 ] ;
 TABLE * table = tables -> table ;
 bool no_global_access = check_access ( thd , SELECT_ACL , "mysql" , 0 , 1 , 1 , 0 ) ;
 char * curr_host = thd -> security_ctx -> priv_host_name ( ) ;
 DBUG_ENTER ( "fill_schema_user_privileges" ) ;
 if ( ! initialized ) DBUG_RETURN ( 0 ) ;
 pthread_mutex_lock ( & acl_cache -> lock ) ;
 for ( counter = 0 ;
 counter < acl_users . elements ;
 counter ++ ) {
 const char * user , * host , * is_grantable = "YES" ;
 acl_user = dynamic_element ( & acl_users , counter , ACL_USER * ) ;
 if ( ! ( user = acl_user -> user ) ) user = "" ;
 if ( ! ( host = acl_user -> host . hostname ) ) host = "" ;
 if ( no_global_access && ( strcmp ( thd -> security_ctx -> priv_user , user ) || my_strcasecmp ( system_charset_info , curr_host , host ) ) ) continue ;
 want_access = acl_user -> access ;
 if ( ! ( want_access & GRANT_ACL ) ) is_grantable = "NO" ;
 strxmov ( buff , "'" , user , "'@'" , host , "'" , NullS ) ;
 if ( ! ( want_access & ~ GRANT_ACL ) ) {
 if ( update_schema_privilege ( thd , table , buff , 0 , 0 , 0 , 0 , STRING_WITH_LEN ( "USAGE" ) , is_grantable ) ) {
 error = 1 ;
 goto err ;
 }
 }
 else {
 uint priv_id ;
 ulong j , test_access = want_access & ~ GRANT_ACL ;
 for ( priv_id = 0 , j = SELECT_ACL ;
 j <= GLOBAL_ACLS ;
 priv_id ++ , j <<= 1 ) {
 if ( test_access & j ) {
 if ( update_schema_privilege ( thd , table , buff , 0 , 0 , 0 , 0 , command_array [ priv_id ] , command_lengths [ priv_id ] , is_grantable ) ) {
 error = 1 ;
 goto err ;
 }
 }
 }
 }
 }
 err : pthread_mutex_unlock ( & acl_cache -> lock ) ;
 DBUG_RETURN ( error ) ;


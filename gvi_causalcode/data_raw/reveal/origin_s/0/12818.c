static int handle_grant_struct ( enum enum_acl_lists struct_no , bool drop , LEX_USER * user_from , LEX_USER * user_to ) {
 int result = 0 ;
 uint idx ;
 uint elements ;
 const char * user ;
 const char * host ;
 ACL_USER * acl_user = NULL ;
 ACL_DB * acl_db = NULL ;
 GRANT_NAME * grant_name = NULL ;
 Dynamic_array < GRANT_NAME * > acl_grant_name ;
 HASH * grant_name_hash = NULL ;
 DBUG_ENTER ( "handle_grant_struct" ) ;
 DBUG_PRINT ( "info" , ( "scan struct: %u search: '%s'@'%s'" , struct_no , user_from -> user . str , user_from -> host . str ) ) ;
 LINT_INIT ( user ) ;
 LINT_INIT ( host ) ;
 safe_mutex_assert_owner ( & acl_cache -> lock ) ;
 switch ( struct_no ) {
 case USER_ACL : elements = acl_users . elements ;
 break ;
 case DB_ACL : elements = acl_dbs . elements ;
 break ;
 case COLUMN_PRIVILEGES_HASH : elements = column_priv_hash . records ;
 grant_name_hash = & column_priv_hash ;
 break ;
 case PROC_PRIVILEGES_HASH : elements = proc_priv_hash . records ;
 grant_name_hash = & proc_priv_hash ;
 break ;
 case FUNC_PRIVILEGES_HASH : elements = func_priv_hash . records ;
 grant_name_hash = & func_priv_hash ;
 break ;
 default : return - 1 ;
 }


 idx < elements ;
 idx ++ ) {
 switch ( struct_no ) {
 case USER_ACL : acl_user = dynamic_element ( & acl_users , idx , ACL_USER * ) ;
 user = acl_user -> user ;
 host = acl_user -> host . hostname ;
 break ;
 case DB_ACL : acl_db = dynamic_element ( & acl_dbs , idx , ACL_DB * ) ;
 user = acl_db -> user ;
 host = acl_db -> host . hostname ;
 break ;
 case COLUMN_PRIVILEGES_HASH : case PROC_PRIVILEGES_HASH : case FUNC_PRIVILEGES_HASH : grant_name = ( GRANT_NAME * ) hash_element ( grant_name_hash , idx ) ;
 user = grant_name -> user ;
 host = grant_name -> host . hostname ;
 break ;
 default : MY_ASSERT_UNREACHABLE ( ) ;
 }
 if ( ! user ) user = "" ;
 if ( ! host ) host = "" ;


 result = 1 ;
 if ( drop ) {
 switch ( struct_no ) {
 case USER_ACL : delete_dynamic_element ( & acl_users , idx ) ;
 elements -- ;
 idx -- ;
 break ;
 case DB_ACL : delete_dynamic_element ( & acl_dbs , idx ) ;
 elements -- ;
 idx -- ;
 break ;
 case COLUMN_PRIVILEGES_HASH : case PROC_PRIVILEGES_HASH : case FUNC_PRIVILEGES_HASH : if ( acl_grant_name . append ( grant_name ) ) DBUG_RETURN ( - 1 ) ;
 break ;
 }
 }
 else if ( user_to ) {
 switch ( struct_no ) {
 case USER_ACL : acl_user -> user = strdup_root ( & mem , user_to -> user . str ) ;
 acl_user -> host . hostname = strdup_root ( & mem , user_to -> host . str ) ;
 break ;
 case DB_ACL : acl_db -> user = strdup_root ( & mem , user_to -> user . str ) ;
 acl_db -> host . hostname = strdup_root ( & mem , user_to -> host . str ) ;
 break ;
 case COLUMN_PRIVILEGES_HASH : case PROC_PRIVILEGES_HASH : case FUNC_PRIVILEGES_HASH : if ( acl_grant_name . append ( grant_name ) ) DBUG_RETURN ( - 1 ) ;
 break ;
 }
 }
 else {
 break ;
 }
 }
 if ( drop || user_to ) {
 for ( int i = 0 ;
 i < acl_grant_name . elements ( ) ;
 ++ i ) {
 grant_name = acl_grant_name . at ( i ) ;
 if ( drop ) {
 my_hash_delete ( grant_name_hash , ( uchar * ) grant_name ) ;
 }
 else {
 char * old_key = grant_name -> hash_key ;
 size_t old_key_length = grant_name -> key_length ;
 grant_name -> set_user_details ( user_to -> host . str , grant_name -> db , user_to -> user . str , grant_name -> tname , TRUE ) ;
 my_hash_update ( grant_name_hash , ( uchar * ) grant_name , ( uchar * ) old_key , old_key_length ) ;
 }
 }
 }


 }
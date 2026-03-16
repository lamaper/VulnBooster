static ACL_USER * find_acl_user ( const char * host , const char * user , my_bool exact ) {
 DBUG_ENTER ( "find_acl_user" ) ;
 DBUG_PRINT ( "enter" , ( "host: '%s' user: '%s'" , host , user ) ) ;
 safe_mutex_assert_owner ( & acl_cache -> lock ) ;
 for ( uint i = 0 ;
 i < acl_users . elements ;
 i ++ ) {
 ACL_USER * acl_user = dynamic_element ( & acl_users , i , ACL_USER * ) ;
 DBUG_PRINT ( "info" , ( "strcmp('%s','%s'), compare_hostname('%s','%s')," , user , acl_user -> user ? acl_user -> user : "" , host , acl_user -> host . hostname ? acl_user -> host . hostname : "" ) ) ;
 if ( ( ! acl_user -> user && ! user [ 0 ] ) || ( acl_user -> user && ! strcmp ( user , acl_user -> user ) ) ) {
 if ( exact ? ! my_strcasecmp ( system_charset_info , host , acl_user -> host . hostname ? acl_user -> host . hostname : "" ) : compare_hostname ( & acl_user -> host , host , host ) ) {
 DBUG_RETURN ( acl_user ) ;
 }
 }
 }
 DBUG_RETURN ( 0 ) ;
 }
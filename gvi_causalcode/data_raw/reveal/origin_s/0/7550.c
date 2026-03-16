ACL_USER * check_acl_user ( LEX_USER * user_name , uint * acl_acl_userdx ) {
 ACL_USER * acl_user = 0 ;
 uint counter ;
 safe_mutex_assert_owner ( & acl_cache -> lock ) ;
 for ( counter = 0 ;
 counter < acl_users . elements ;
 counter ++ ) {
 const char * user , * host ;
 acl_user = dynamic_element ( & acl_users , counter , ACL_USER * ) ;
 if ( ! ( user = acl_user -> user ) ) user = "" ;
 if ( ! ( host = acl_user -> host . hostname ) ) host = "" ;
 if ( ! strcmp ( user_name -> user . str , user ) && ! my_strcasecmp ( system_charset_info , user_name -> host . str , host ) ) break ;
 }
 if ( counter == acl_users . elements ) return 0 ;
 * acl_acl_userdx = counter ;
 return acl_user ;
 }
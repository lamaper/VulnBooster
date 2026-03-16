static void init_check_host ( void ) {
 DBUG_ENTER ( "init_check_host" ) ;
 VOID ( my_init_dynamic_array ( & acl_wild_hosts , sizeof ( struct acl_host_and_ip ) , acl_users . elements , 1 ) ) ;
 VOID ( hash_init ( & acl_check_hosts , system_charset_info , acl_users . elements , 0 , 0 , ( hash_get_key ) check_get_key , 0 , 0 ) ) ;
 if ( ! allow_all_hosts ) {
 for ( uint i = 0 ;
 i < acl_users . elements ;
 i ++ ) {
 ACL_USER * acl_user = dynamic_element ( & acl_users , i , ACL_USER * ) ;
 if ( strchr ( acl_user -> host . hostname , wild_many ) || strchr ( acl_user -> host . hostname , wild_one ) || acl_user -> host . ip_mask ) {
 uint j ;
 for ( j = 0 ;
 j < acl_wild_hosts . elements ;
 j ++ ) {
 acl_host_and_ip * acl = dynamic_element ( & acl_wild_hosts , j , acl_host_and_ip * ) ;
 if ( ! my_strcasecmp ( system_charset_info , acl_user -> host . hostname , acl -> hostname ) ) break ;
 }
 if ( j == acl_wild_hosts . elements ) ( void ) push_dynamic ( & acl_wild_hosts , ( uchar * ) & acl_user -> host ) ;
 }
 else if ( ! hash_search ( & acl_check_hosts , ( uchar * ) acl_user -> host . hostname , strlen ( acl_user -> host . hostname ) ) ) {
 if ( my_hash_insert ( & acl_check_hosts , ( uchar * ) acl_user ) ) {
 allow_all_hosts = 1 ;
 DBUG_VOID_RETURN ;
 }
 }
 }
 }
 freeze_size ( & acl_wild_hosts ) ;
 freeze_size ( & acl_check_hosts . array ) ;
 DBUG_VOID_RETURN ;
 }
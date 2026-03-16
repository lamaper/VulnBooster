static void acl_update_user ( const char * user , const char * host , const char * password , uint password_len , enum SSL_type ssl_type , const char * ssl_cipher , const char * x509_issuer , const char * x509_subject , USER_RESOURCES * mqh , ulong privileges ) {
 safe_mutex_assert_owner ( & acl_cache -> lock ) ;
 for ( uint i = 0 ;
 i < acl_users . elements ;
 i ++ ) {
 ACL_USER * acl_user = dynamic_element ( & acl_users , i , ACL_USER * ) ;
 if ( ( ! acl_user -> user && ! user [ 0 ] ) || ( acl_user -> user && ! strcmp ( user , acl_user -> user ) ) ) {
 if ( ( ! acl_user -> host . hostname && ! host [ 0 ] ) || ( acl_user -> host . hostname && ! my_strcasecmp ( system_charset_info , host , acl_user -> host . hostname ) ) ) {
 acl_user -> access = privileges ;
 if ( mqh -> specified_limits & USER_RESOURCES : : QUERIES_PER_HOUR ) acl_user -> user_resource . questions = mqh -> questions ;
 if ( mqh -> specified_limits & USER_RESOURCES : : UPDATES_PER_HOUR ) acl_user -> user_resource . updates = mqh -> updates ;
 if ( mqh -> specified_limits & USER_RESOURCES : : CONNECTIONS_PER_HOUR ) acl_user -> user_resource . conn_per_hour = mqh -> conn_per_hour ;
 if ( mqh -> specified_limits & USER_RESOURCES : : USER_CONNECTIONS ) acl_user -> user_resource . user_conn = mqh -> user_conn ;
 if ( ssl_type != SSL_TYPE_NOT_SPECIFIED ) {
 acl_user -> ssl_type = ssl_type ;
 acl_user -> ssl_cipher = ( ssl_cipher ? strdup_root ( & mem , ssl_cipher ) : 0 ) ;
 acl_user -> x509_issuer = ( x509_issuer ? strdup_root ( & mem , x509_issuer ) : 0 ) ;
 acl_user -> x509_subject = ( x509_subject ? strdup_root ( & mem , x509_subject ) : 0 ) ;
 }
 if ( password ) set_user_salt ( acl_user , password , password_len ) ;
 break ;
 }
 }
 }
 }
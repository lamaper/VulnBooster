void get_mqh ( const char * user , const char * host , USER_CONN * uc ) {
 ACL_USER * acl_user ;
 pthread_mutex_lock ( & acl_cache -> lock ) ;
 if ( initialized && ( acl_user = find_acl_user ( host , user , FALSE ) ) ) uc -> user_resources = acl_user -> user_resource ;
 else bzero ( ( char * ) & uc -> user_resources , sizeof ( uc -> user_resources ) ) ;
 pthread_mutex_unlock ( & acl_cache -> lock ) ;
 }
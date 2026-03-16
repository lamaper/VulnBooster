bool is_acl_user ( const char * host , const char * user ) {
 bool res ;
 if ( ! initialized ) return TRUE ;
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 res = find_acl_user ( host , user , TRUE ) != NULL ;
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 return res ;
 }
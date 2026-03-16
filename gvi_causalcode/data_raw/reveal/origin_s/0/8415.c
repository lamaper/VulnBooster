bool acl_check_host ( const char * host , const char * ip ) {
 if ( allow_all_hosts ) return 0 ;
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 if ( ( host && hash_search ( & acl_check_hosts , ( uchar * ) host , strlen ( host ) ) ) || ( ip && hash_search ( & acl_check_hosts , ( uchar * ) ip , strlen ( ip ) ) ) ) {
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 return 0 ;
 }
 for ( uint i = 0 ;
 i < acl_wild_hosts . elements ;
 i ++ ) {
 acl_host_and_ip * acl = dynamic_element ( & acl_wild_hosts , i , acl_host_and_ip * ) ;
 if ( compare_hostname ( acl , host , ip ) ) {
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 return 0 ;
 }
 }
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 return 1 ;
 }
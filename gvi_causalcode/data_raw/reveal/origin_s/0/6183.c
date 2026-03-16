void rebuild_check_host ( void ) {
 delete_dynamic ( & acl_wild_hosts ) ;
 hash_free ( & acl_check_hosts ) ;
 init_check_host ( ) ;
 }
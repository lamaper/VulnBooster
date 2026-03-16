void acl_free ( bool end ) {
 free_root ( & mem , MYF ( 0 ) ) ;
 delete_dynamic ( & acl_hosts ) ;
 delete_dynamic ( & acl_users ) ;
 delete_dynamic ( & acl_dbs ) ;
 delete_dynamic ( & acl_wild_hosts ) ;
 hash_free ( & acl_check_hosts ) ;
 if ( ! end ) acl_cache -> clear ( 1 ) ;
 else {
 delete acl_cache ;
 acl_cache = 0 ;
 }
 }
my_bool acl_init ( bool dont_read_acl_tables ) {
 THD * thd ;
 my_bool return_val ;
 DBUG_ENTER ( "acl_init" ) ;
 acl_cache = new hash_filo ( ACL_CACHE_SIZE , 0 , 0 , ( hash_get_key ) acl_entry_get_key , ( hash_free_key ) free , & my_charset_utf8_bin ) ;
 if ( dont_read_acl_tables ) {
 DBUG_RETURN ( 0 ) ;
 }
 if ( ! ( thd = new THD ) ) DBUG_RETURN ( 1 ) ;
 thd -> thread_stack = ( char * ) & thd ;
 thd -> store_globals ( ) ;
 lex_start ( thd ) ;
 return_val = acl_reload ( thd ) ;
 delete thd ;
 my_pthread_setspecific_ptr ( THR_THD , 0 ) ;
 DBUG_RETURN ( return_val ) ;
 }
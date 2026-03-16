my_bool acl_reload ( THD * thd ) {
 TABLE_LIST tables [ 3 ] ;
 DYNAMIC_ARRAY old_acl_hosts , old_acl_users , old_acl_dbs ;
 MEM_ROOT old_mem ;
 bool old_initialized ;
 my_bool return_val = TRUE ;
 DBUG_ENTER ( "acl_reload" ) ;
 if ( thd -> locked_tables ) {
 thd -> lock = thd -> locked_tables ;
 thd -> locked_tables = 0 ;
 close_thread_tables ( thd ) ;
 }
 bzero ( ( char * ) tables , sizeof ( tables ) ) ;
 tables [ 0 ] . alias = tables [ 0 ] . table_name = ( char * ) "host" ;
 tables [ 1 ] . alias = tables [ 1 ] . table_name = ( char * ) "user" ;
 tables [ 2 ] . alias = tables [ 2 ] . table_name = ( char * ) "db" ;
 tables [ 0 ] . db = tables [ 1 ] . db = tables [ 2 ] . db = ( char * ) "mysql" ;
 tables [ 0 ] . next_local = tables [ 0 ] . next_global = tables + 1 ;
 tables [ 1 ] . next_local = tables [ 1 ] . next_global = tables + 2 ;
 tables [ 0 ] . lock_type = tables [ 1 ] . lock_type = tables [ 2 ] . lock_type = TL_READ ;
 tables [ 0 ] . skip_temporary = tables [ 1 ] . skip_temporary = tables [ 2 ] . skip_temporary = TRUE ;
 if ( simple_open_n_lock_tables ( thd , tables ) ) {
 if ( thd -> main_da . is_error ( ) ) sql_print_error ( "Fatal error: Can't open and lock privilege tables: %s" , thd -> main_da . message ( ) ) ;
 goto end ;
 }
 if ( ( old_initialized = initialized ) ) VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 old_acl_hosts = acl_hosts ;
 old_acl_users = acl_users ;
 old_acl_dbs = acl_dbs ;
 old_mem = mem ;
 delete_dynamic ( & acl_wild_hosts ) ;
 hash_free ( & acl_check_hosts ) ;
 if ( ( return_val = acl_load ( thd , tables ) ) ) {
 DBUG_PRINT ( "error" , ( "Reverting to old privileges" ) ) ;
 acl_free ( ) ;
 acl_hosts = old_acl_hosts ;
 acl_users = old_acl_users ;
 acl_dbs = old_acl_dbs ;
 mem = old_mem ;
 init_check_host ( ) ;
 }
 else {
 free_root ( & old_mem , MYF ( 0 ) ) ;
 delete_dynamic ( & old_acl_hosts ) ;
 delete_dynamic ( & old_acl_users ) ;
 delete_dynamic ( & old_acl_dbs ) ;
 }
 if ( old_initialized ) VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 end : close_thread_tables ( thd ) ;
 DBUG_RETURN ( return_val ) ;
 }
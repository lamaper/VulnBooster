static my_bool grant_reload_procs_priv ( THD * thd ) {
 HASH old_proc_priv_hash , old_func_priv_hash ;
 TABLE_LIST table ;
 my_bool return_val = FALSE ;
 DBUG_ENTER ( "grant_reload_procs_priv" ) ;
 bzero ( ( char * ) & table , sizeof ( table ) ) ;
 table . alias = table . table_name = ( char * ) "procs_priv" ;
 table . db = ( char * ) "mysql" ;
 table . lock_type = TL_READ ;
 table . skip_temporary = 1 ;
 if ( simple_open_n_lock_tables ( thd , & table ) ) {
 close_thread_tables ( thd ) ;
 DBUG_RETURN ( TRUE ) ;
 }
 rw_wrlock ( & LOCK_grant ) ;
 old_proc_priv_hash = proc_priv_hash ;
 old_func_priv_hash = func_priv_hash ;
 if ( ( return_val = grant_load_procs_priv ( table . table ) ) ) {
 DBUG_PRINT ( "error" , ( "Reverting to old privileges" ) ) ;
 grant_free ( ) ;
 proc_priv_hash = old_proc_priv_hash ;
 func_priv_hash = old_func_priv_hash ;
 }
 else {
 hash_free ( & old_proc_priv_hash ) ;
 hash_free ( & old_func_priv_hash ) ;
 }
 rw_unlock ( & LOCK_grant ) ;
 close_thread_tables ( thd ) ;
 DBUG_RETURN ( return_val ) ;
 }
my_bool grant_reload ( THD * thd ) {
 TABLE_LIST tables [ 2 ] ;
 HASH old_column_priv_hash ;
 MEM_ROOT old_mem ;
 my_bool return_val = 1 ;
 DBUG_ENTER ( "grant_reload" ) ;
 if ( ! initialized ) DBUG_RETURN ( 0 ) ;
 bzero ( ( char * ) tables , sizeof ( tables ) ) ;
 tables [ 0 ] . alias = tables [ 0 ] . table_name = ( char * ) "tables_priv" ;
 tables [ 1 ] . alias = tables [ 1 ] . table_name = ( char * ) "columns_priv" ;
 tables [ 0 ] . db = tables [ 1 ] . db = ( char * ) "mysql" ;
 tables [ 0 ] . next_local = tables [ 0 ] . next_global = tables + 1 ;
 tables [ 0 ] . lock_type = tables [ 1 ] . lock_type = TL_READ ;
 tables [ 0 ] . skip_temporary = tables [ 1 ] . skip_temporary = TRUE ;
 if ( simple_open_n_lock_tables ( thd , tables ) ) goto end ;
 rw_wrlock ( & LOCK_grant ) ;
 old_column_priv_hash = column_priv_hash ;
 old_mem = memex ;
 init_sql_alloc ( & memex , ACL_ALLOC_BLOCK_SIZE , 0 ) ;
 if ( ( return_val = grant_load ( thd , tables ) ) ) {
 DBUG_PRINT ( "error" , ( "Reverting to old privileges" ) ) ;
 grant_free ( ) ;
 column_priv_hash = old_column_priv_hash ;
 memex = old_mem ;
 }
 else {
 hash_free ( & old_column_priv_hash ) ;
 free_root ( & old_mem , MYF ( 0 ) ) ;
 }
 rw_unlock ( & LOCK_grant ) ;
 close_thread_tables ( thd ) ;
 if ( grant_reload_procs_priv ( thd ) ) return_val = 1 ;
 rw_wrlock ( & LOCK_grant ) ;
 grant_version ++ ;
 rw_unlock ( & LOCK_grant ) ;
 end : DBUG_RETURN ( return_val ) ;
 }
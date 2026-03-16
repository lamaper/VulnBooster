void refresh_status ( THD * thd ) {
 mysql_mutex_lock ( & LOCK_status ) ;
 add_to_status ( & global_status_var , & thd -> status_var ) ;
 bzero ( ( uchar * ) & thd -> status_var , sizeof ( thd -> status_var ) ) ;
 bzero ( ( uchar * ) & thd -> org_status_var , sizeof ( thd -> org_status_var ) ) ;
 thd -> start_bytes_received = 0 ;
 reset_status_vars ( ) ;
 process_key_caches ( reset_key_cache_counters , 0 ) ;
 flush_status_time = time ( ( time_t * ) 0 ) ;
 mysql_mutex_unlock ( & LOCK_status ) ;
 mysql_mutex_lock ( & LOCK_thread_count ) ;
 max_used_connections = thread_count - delayed_insert_threads ;
 mysql_mutex_unlock ( & LOCK_thread_count ) ;
 }
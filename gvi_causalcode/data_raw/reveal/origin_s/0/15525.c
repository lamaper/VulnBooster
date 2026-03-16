static int init_thread_environment ( ) {
 mysql_mutex_init ( key_LOCK_thread_count , & LOCK_thread_count , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_status , & LOCK_status , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_delayed_insert , & LOCK_delayed_insert , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_delayed_status , & LOCK_delayed_status , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_delayed_create , & LOCK_delayed_create , MY_MUTEX_INIT_SLOW ) ;
 mysql_mutex_init ( key_LOCK_crypt , & LOCK_crypt , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_user_conn , & LOCK_user_conn , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_active_mi , & LOCK_active_mi , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_global_system_variables , & LOCK_global_system_variables , MY_MUTEX_INIT_FAST ) ;
 mysql_rwlock_init ( key_rwlock_LOCK_system_variables_hash , & LOCK_system_variables_hash ) ;
 mysql_mutex_init ( key_LOCK_prepared_stmt_count , & LOCK_prepared_stmt_count , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_error_messages , & LOCK_error_messages , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_uuid_short_generator , & LOCK_short_uuid_generator , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_connection_count , & LOCK_connection_count , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_stats , & LOCK_stats , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_global_user_client_stats , & LOCK_global_user_client_stats , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_global_table_stats , & LOCK_global_table_stats , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_global_index_stats , & LOCK_global_index_stats , MY_MUTEX_INIT_FAST ) ;
 mysql_mutex_init ( key_LOCK_prepare_ordered , & LOCK_prepare_ordered , MY_MUTEX_INIT_SLOW ) ;
 mysql_mutex_init ( key_LOCK_commit_ordered , & LOCK_commit_ordered , MY_MUTEX_INIT_SLOW ) ;


 for ( int i = 0 ;
 i < CRYPTO_num_locks ( ) ;
 ++ i ) mysql_rwlock_init ( key_rwlock_openssl , & openssl_stdlocks [ i ] . lock ) ;
 CRYPTO_set_dynlock_create_callback ( openssl_dynlock_create ) ;
 CRYPTO_set_dynlock_destroy_callback ( openssl_dynlock_destroy ) ;
 CRYPTO_set_dynlock_lock_callback ( openssl_lock ) ;
 CRYPTO_set_locking_callback ( openssl_lock_function ) ;

 mysql_rwlock_init ( key_rwlock_LOCK_sys_init_slave , & LOCK_sys_init_slave ) ;
 mysql_rwlock_init ( key_rwlock_LOCK_grant , & LOCK_grant ) ;
 mysql_cond_init ( key_COND_thread_count , & COND_thread_count , NULL ) ;
 mysql_cond_init ( key_COND_thread_cache , & COND_thread_cache , NULL ) ;
 mysql_cond_init ( key_COND_flush_thread_cache , & COND_flush_thread_cache , NULL ) ;

 mysql_cond_init ( key_COND_rpl_status , & COND_rpl_status , NULL ) ;

 mysql_cond_init ( key_COND_server_started , & COND_server_started , NULL ) ;
 sp_cache_init ( ) ;


 ( void ) pthread_attr_setdetachstate ( & connection_attrib , PTHREAD_CREATE_DETACHED ) ;
 pthread_attr_setscope ( & connection_attrib , PTHREAD_SCOPE_SYSTEM ) ;
 if ( pthread_key_create ( & THR_THD , NULL ) || pthread_key_create ( & THR_MALLOC , NULL ) ) {
 sql_print_error ( "Can't create thread-keys" ) ;
 return 1 ;
 }
 return 0 ;
 }
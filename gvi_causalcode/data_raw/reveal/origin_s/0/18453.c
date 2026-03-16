static bool cache_thread ( ) {
 mysql_mutex_assert_owner ( & LOCK_thread_count ) ;
 if ( cached_thread_count < thread_cache_size && ! abort_loop && ! kill_cached_threads ) {
 DBUG_PRINT ( "info" , ( "Adding thread to cache" ) ) ;
 cached_thread_count ++ ;


 cached_thread_count -- ;
 if ( kill_cached_threads ) mysql_cond_signal ( & COND_flush_thread_cache ) ;
 if ( wake_thread ) {
 THD * thd ;
 wake_thread -- ;
 thd = thread_cache . get ( ) ;
 thd -> thread_stack = ( char * ) & thd ;
 ( void ) thd -> store_globals ( ) ;

 PSI_thread * psi = PSI_server -> new_thread ( key_thread_one_connection , thd , thd -> thread_id ) ;
 if ( likely ( psi != NULL ) ) PSI_server -> set_thread ( psi ) ;
 }

 thd -> thr_create_utime = microsecond_interval_timer ( ) ;
 thd -> start_utime = thd -> thr_create_utime ;
 threads . append ( thd ) ;
 return ( 1 ) ;
 }
 }
 return ( 0 ) ;
 }
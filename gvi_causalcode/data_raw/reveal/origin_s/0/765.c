static void create_new_thread ( THD * thd ) {
 DBUG_ENTER ( "create_new_thread" ) ;
 mysql_mutex_lock ( & LOCK_connection_count ) ;
 if ( * thd -> scheduler -> connection_count >= * thd -> scheduler -> max_connections + 1 || abort_loop ) {
 mysql_mutex_unlock ( & LOCK_connection_count ) ;
 DBUG_PRINT ( "error" , ( "Too many connections" ) ) ;
 close_connection ( thd , ER_CON_COUNT_ERROR ) ;
 statistic_increment ( denied_connections , & LOCK_status ) ;
 delete thd ;
 DBUG_VOID_RETURN ;
 }
 ++ * thd -> scheduler -> connection_count ;
 if ( connection_count + extra_connection_count > max_used_connections ) max_used_connections = connection_count + extra_connection_count ;
 mysql_mutex_unlock ( & LOCK_connection_count ) ;
 mysql_mutex_lock ( & LOCK_thread_count ) ;
 thd -> thread_id = thd -> variables . pseudo_thread_id = thread_id ++ ;
 thread_count ++ ;
 MYSQL_CALLBACK ( thd -> scheduler , add_connection , ( thd ) ) ;
 DBUG_VOID_RETURN ;
 }
void unlink_thd ( THD * thd ) {
 DBUG_ENTER ( "unlink_thd" ) ;
 DBUG_PRINT ( "enter" , ( "thd: 0x%lx" , ( long ) thd ) ) ;
 thd_cleanup ( thd ) ;
 dec_connection_count ( thd ) ;
 thd -> add_status_to_global ( ) ;
 mysql_mutex_lock ( & LOCK_thread_count ) ;
 thd -> unlink ( ) ;
 DBUG_EXECUTE_IF ( "sleep_after_lock_thread_count_before_delete_thd" , sleep ( 5 ) ;
 ) ;
 if ( unlikely ( abort_loop ) ) {
 delete thd ;
 thd = 0 ;
 }
 thread_count -- ;
 mysql_mutex_unlock ( & LOCK_thread_count ) ;
 delete thd ;
 DBUG_VOID_RETURN ;
 }
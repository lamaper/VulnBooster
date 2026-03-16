static void bootstrap ( MYSQL_FILE * file ) {
 DBUG_ENTER ( "bootstrap" ) ;
 THD * thd = new THD ;
 thd -> bootstrap = 1 ;
 my_net_init ( & thd -> net , ( st_vio * ) 0 ) ;
 thd -> max_client_packet_length = thd -> net . max_packet ;
 thd -> security_ctx -> master_access = ~ ( ulong ) 0 ;
 thd -> thread_id = thd -> variables . pseudo_thread_id = thread_id ++ ;
 thread_count ++ ;
 in_bootstrap = TRUE ;
 bootstrap_file = file ;

 if ( ( error = mysql_thread_create ( key_thread_bootstrap , & thd -> real_id , & connection_attrib , handle_bootstrap , ( void * ) thd ) ) ) {
 sql_print_warning ( "Can't create thread to handle bootstrap (errno= %d)" , error ) ;
 bootstrap_error = - 1 ;
 DBUG_VOID_RETURN ;
 }
 mysql_mutex_lock ( & LOCK_thread_count ) ;
 while ( in_bootstrap ) {
 mysql_cond_wait ( & COND_thread_count , & LOCK_thread_count ) ;
 DBUG_PRINT ( "quit" , ( "One thread died (count=%u)" , thread_count ) ) ;
 }
 mysql_mutex_unlock ( & LOCK_thread_count ) ;

 do_handle_bootstrap ( thd ) ;

 }
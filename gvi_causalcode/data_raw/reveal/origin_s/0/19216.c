static void close_connections ( void ) {


 kill_cached_threads ++ ;
 flush_thread_cache ( ) ;

 mysql_mutex_lock ( & LOCK_thread_count ) ;
 while ( select_thread_in_use ) {
 struct timespec abstime ;
 int error ;
 LINT_INIT ( error ) ;
 DBUG_PRINT ( "info" , ( "Waiting for select thread" ) ) ;


 for ( uint tmp = 0 ;
 tmp < 10 && select_thread_in_use ;
 tmp ++ ) {
 error = mysql_cond_timedwait ( & COND_thread_count , & LOCK_thread_count , & abstime ) ;
 if ( error != EINTR ) break ;
 }


 }
 mysql_mutex_unlock ( & LOCK_thread_count ) ;

 if ( ! opt_disable_networking ) {
 if ( base_ip_sock != INVALID_SOCKET ) {
 ( void ) mysql_socket_shutdown ( base_ip_sock , SHUT_RDWR ) ;
 ( void ) closesocket ( base_ip_sock ) ;
 base_ip_sock = INVALID_SOCKET ;
 }
 if ( extra_ip_sock != INVALID_SOCKET ) {
 ( void ) mysql_socket_shutdown ( extra_ip_sock , SHUT_RDWR ) ;
 ( void ) closesocket ( extra_ip_sock ) ;
 extra_ip_sock = INVALID_SOCKET ;
 }
 }

 HANDLE temp ;
 DBUG_PRINT ( "quit" , ( "Closing named pipes" ) ) ;
 if ( ( temp = CreateFile ( pipe_name , GENERIC_READ | GENERIC_WRITE , 0 , NULL , OPEN_EXISTING , 0 , NULL ) ) != INVALID_HANDLE_VALUE ) {
 WaitNamedPipe ( pipe_name , 1000 ) ;
 DWORD dwMode = PIPE_READMODE_BYTE | PIPE_WAIT ;
 SetNamedPipeHandleState ( temp , & dwMode , NULL , NULL ) ;
 CancelIo ( temp ) ;
 DisconnectNamedPipe ( temp ) ;
 CloseHandle ( temp ) ;
 }
 }

 ( void ) mysql_socket_shutdown ( unix_sock , SHUT_RDWR ) ;
 ( void ) closesocket ( unix_sock ) ;
 ( void ) unlink ( mysqld_unix_port ) ;
 unix_sock = INVALID_SOCKET ;
 }

 THD * tmp ;
 mysql_mutex_lock ( & LOCK_thread_count ) ;
 I_List_iterator < THD > it ( threads ) ;
 while ( ( tmp = it ++ ) ) {
 DBUG_PRINT ( "quit" , ( "Informing thread %ld that it's time to die" , tmp -> thread_id ) ) ;
 if ( tmp -> slave_thread ) continue ;
 tmp -> killed = KILL_SERVER_HARD ;
 MYSQL_CALLBACK ( thread_scheduler , post_kill_notification , ( tmp ) ) ;
 mysql_mutex_lock ( & tmp -> LOCK_thd_data ) ;
 if ( tmp -> mysys_var ) {
 tmp -> mysys_var -> abort = 1 ;
 mysql_mutex_lock ( & tmp -> mysys_var -> mutex ) ;
 if ( tmp -> mysys_var -> current_cond ) {
 uint i ;
 for ( i = 0 ;
 i < 2 ;
 i ++ ) {
 int ret = mysql_mutex_trylock ( tmp -> mysys_var -> current_mutex ) ;
 mysql_cond_broadcast ( tmp -> mysys_var -> current_cond ) ;
 if ( ! ret ) {
 mysql_mutex_unlock ( tmp -> mysys_var -> current_mutex ) ;
 break ;
 }
 sleep ( 1 ) ;
 }
 }
 mysql_mutex_unlock ( & tmp -> mysys_var -> mutex ) ;
 }
 mysql_mutex_unlock ( & tmp -> LOCK_thd_data ) ;
 }
 mysql_mutex_unlock ( & LOCK_thread_count ) ;
 Events : : deinit ( ) ;
 end_slave ( ) ;
 for ( int i = 0 ;
 thread_count && i < 100 ;
 i ++ ) my_sleep ( 20000 ) ;
 for ( ;
 ;
 ) {
 DBUG_PRINT ( "quit" , ( "Locking LOCK_thread_count" ) ) ;
 mysql_mutex_lock ( & LOCK_thread_count ) ;
 if ( ! ( tmp = threads . get ( ) ) ) {
 DBUG_PRINT ( "quit" , ( "Unlocking LOCK_thread_count" ) ) ;
 mysql_mutex_unlock ( & LOCK_thread_count ) ;
 break ;
 }

 if ( global_system_variables . log_warnings ) sql_print_warning ( ER_DEFAULT ( ER_FORCING_CLOSE ) , my_progname , tmp -> thread_id , ( tmp -> main_security_ctx . user ? tmp -> main_security_ctx . user : "" ) ) ;
 close_connection ( tmp , ER_SERVER_SHUTDOWN ) ;
 }

 mysql_mutex_unlock ( & LOCK_thread_count ) ;
 }
 DBUG_PRINT ( "quit" , ( "Waiting for threads to die (count=%u)" , thread_count ) ) ;
 mysql_mutex_lock ( & LOCK_thread_count ) ;
 while ( thread_count ) {
 mysql_cond_wait ( & COND_thread_count , & LOCK_thread_count ) ;
 DBUG_PRINT ( "quit" , ( "One thread died (count=%u)" , thread_count ) ) ;
 }
 mysql_mutex_unlock ( & LOCK_thread_count ) ;
 DBUG_PRINT ( "quit" , ( "close_connections thread" ) ) ;
 DBUG_VOID_RETURN ;
 }
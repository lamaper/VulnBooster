void handle_connections_sockets ( ) {
 my_socket UNINIT_VAR ( sock ) , UNINIT_VAR ( new_sock ) ;
 uint error_count = 0 ;
 THD * thd ;
 struct sockaddr_storage cAddr ;
 int ip_flags __attribute__ ( ( unused ) ) = 0 ;
 int socket_flags __attribute__ ( ( unused ) ) = 0 ;
 int extra_ip_flags __attribute__ ( ( unused ) ) = 0 ;
 int flags = 0 , retval ;
 st_vio * vio_tmp ;

 struct pollfd fds [ 3 ] ;

 fds [ socket_count ] . events = POLLIN ;
 socket_count ++ # else fd_set readFDs , clientFDs ;
 uint max_used_connection = ( uint ) max ( max ( base_ip_sock , unix_sock ) , extra_ip_sock ) + 1 ;


 if ( base_ip_sock != INVALID_SOCKET ) {
 setup_fds ( base_ip_sock ) ;
 ip_flags = fcntl ( base_ip_sock , F_GETFL , 0 ) ;
 }
 if ( extra_ip_sock != INVALID_SOCKET ) {
 setup_fds ( extra_ip_sock ) ;
 extra_ip_flags = fcntl ( extra_ip_sock , F_GETFL , 0 ) ;
 }

 socket_flags = fcntl ( unix_sock , F_GETFL , 0 ) ;

 MAYBE_BROKEN_SYSCALL ;
 while ( ! abort_loop ) {


 retval = select ( ( int ) max_used_connection , & readFDs , 0 , 0 , 0 ) ;

 if ( socket_errno != SOCKET_EINTR ) {
 if ( ! select_errors ++ && ! abort_loop ) sql_print_error ( "mysqld: Got error %d from select" , socket_errno ) ;
 }
 MAYBE_BROKEN_SYSCALL continue ;
 }
 if ( abort_loop ) {
 MAYBE_BROKEN_SYSCALL ;
 break ;
 }

 i < socket_count ;
 ++ i ) {
 if ( fds [ i ] . revents & POLLIN ) {
 sock = fds [ i ] . fd ;
 flags = fcntl ( sock , F_GETFL , 0 ) ;
 break ;
 }
 }

 sock = base_ip_sock ;
 flags = ip_flags ;
 }
 else if ( FD_ISSET ( extra_ip_sock , & readFDs ) ) {
 sock = extra_ip_sock ;
 flags = extra_ip_flags ;
 }
 else {
 sock = unix_sock ;
 flags = socket_flags ;
 }





 retry < MAX_ACCEPT_RETRY ;
 retry ++ ) {
 size_socket length = sizeof ( struct sockaddr_storage ) ;
 new_sock = accept ( sock , ( struct sockaddr * ) ( & cAddr ) , & length ) ;
 if ( new_sock != INVALID_SOCKET || ( socket_errno != SOCKET_EINTR && socket_errno != SOCKET_EAGAIN ) ) break ;
 MAYBE_BROKEN_SYSCALL ;

 if ( retry == MAX_ACCEPT_RETRY - 1 ) fcntl ( sock , F_SETFL , flags ) ;
 }



 if ( ( error_count ++ & 255 ) == 0 ) sql_perror ( "Error in accept" ) ;
 MAYBE_BROKEN_SYSCALL ;
 if ( socket_errno == SOCKET_ENFILE || socket_errno == SOCKET_EMFILE ) sleep ( 1 ) ;
 continue ;
 }

 if ( sock == base_ip_sock || sock == extra_ip_sock ) {
 struct request_info req ;
 signal ( SIGCHLD , SIG_DFL ) ;
 request_init ( & req , RQ_DAEMON , libwrapName , RQ_FILE , new_sock , NULL ) ;
 my_fromhost ( & req ) ;
 if ( ! my_hosts_access ( & req ) ) {
 syslog ( deny_severity , "refused connect from %s" , my_eval_client ( & req ) ) ;
 if ( req . sink ) ( ( void ( * ) ( int ) ) req . sink ) ( req . fd ) ;
 ( void ) mysql_socket_shutdown ( new_sock , SHUT_RDWR ) ;
 ( void ) closesocket ( new_sock ) ;
 continue ;
 }
 }
 }

 size_socket dummyLen ;
 struct sockaddr_storage dummy ;
 dummyLen = sizeof ( dummy ) ;
 if ( getsockname ( new_sock , ( struct sockaddr * ) & dummy , ( SOCKET_SIZE_TYPE * ) & dummyLen ) < 0 ) {
 sql_perror ( "Error on new connection socket" ) ;
 ( void ) mysql_socket_shutdown ( new_sock , SHUT_RDWR ) ;
 ( void ) closesocket ( new_sock ) ;
 continue ;
 }
 }
 if ( ! ( thd = new THD ) ) {
 ( void ) mysql_socket_shutdown ( new_sock , SHUT_RDWR ) ;
 ( void ) closesocket ( new_sock ) ;
 continue ;
 }
 if ( ! ( vio_tmp = vio_new ( new_sock , sock == unix_sock ? VIO_TYPE_SOCKET : VIO_TYPE_TCPIP , sock == unix_sock ? VIO_LOCALHOST : 0 ) ) || my_net_init ( & thd -> net , vio_tmp ) ) {
 if ( vio_tmp && thd -> net . vio != vio_tmp ) vio_delete ( vio_tmp ) ;
 else {
 ( void ) mysql_socket_shutdown ( new_sock , SHUT_RDWR ) ;
 ( void ) closesocket ( new_sock ) ;
 }
 delete thd ;
 continue ;
 }
 if ( sock == unix_sock ) thd -> security_ctx -> host = ( char * ) my_localhost ;
 if ( sock == extra_ip_sock ) {
 thd -> extra_port = 1 ;
 thd -> scheduler = extra_thread_scheduler ;
 }
 create_new_thread ( thd ) ;
 }
 DBUG_VOID_RETURN ;
 }
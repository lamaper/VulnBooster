static void network_init ( void ) {

 int arg ;

 if ( MYSQL_CALLBACK_ELSE ( thread_scheduler , init , ( ) , 0 ) ) unireg_abort ( 1 ) ;
 set_ports ( ) ;
 if ( report_port == 0 ) {
 report_port = mysqld_port ;
 }


 if ( mysqld_port ) base_ip_sock = activate_tcp_port ( mysqld_port ) ;
 if ( mysqld_extra_port ) extra_ip_sock = activate_tcp_port ( mysqld_extra_port ) ;
 }

 strxnmov ( pipe_name , sizeof ( pipe_name ) - 1 , "\\\\.\\pipe\\" , mysqld_unix_port , NullS ) ;
 bzero ( ( char * ) & saPipeSecurity , sizeof ( saPipeSecurity ) ) ;
 bzero ( ( char * ) & sdPipeDescriptor , sizeof ( sdPipeDescriptor ) ) ;
 if ( ! InitializeSecurityDescriptor ( & sdPipeDescriptor , SECURITY_DESCRIPTOR_REVISION ) ) {
 sql_perror ( "Can't start server : Initialize security descriptor" ) ;
 unireg_abort ( 1 ) ;
 }
 if ( ! SetSecurityDescriptorDacl ( & sdPipeDescriptor , TRUE , NULL , FALSE ) ) {
 sql_perror ( "Can't start server : Set security descriptor" ) ;
 unireg_abort ( 1 ) ;
 }
 saPipeSecurity . nLength = sizeof ( SECURITY_ATTRIBUTES ) ;
 saPipeSecurity . lpSecurityDescriptor = & sdPipeDescriptor ;
 saPipeSecurity . bInheritHandle = FALSE ;
 if ( ( hPipe = CreateNamedPipe ( pipe_name , PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED | FILE_FLAG_FIRST_PIPE_INSTANCE , PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT , PIPE_UNLIMITED_INSTANCES , ( int ) global_system_variables . net_buffer_length , ( int ) global_system_variables . net_buffer_length , NMPWAIT_USE_DEFAULT_WAIT , & saPipeSecurity ) ) == INVALID_HANDLE_VALUE ) {
 sql_perror ( "Create named pipe failed" ) ;
 unireg_abort ( 1 ) ;
 }
 }

 DBUG_PRINT ( "general" , ( "UNIX Socket is %s" , mysqld_unix_port ) ) ;
 if ( strlen ( mysqld_unix_port ) > ( sizeof ( UNIXaddr . sun_path ) - 1 ) ) {
 sql_print_error ( "The socket file path is too long (> %u): %s" , ( uint ) sizeof ( UNIXaddr . sun_path ) - 1 , mysqld_unix_port ) ;
 unireg_abort ( 1 ) ;
 }
 if ( ( unix_sock = socket ( AF_UNIX , SOCK_STREAM , 0 ) ) < 0 ) {
 sql_perror ( "Can't start server : UNIX Socket " ) ;
 unireg_abort ( 1 ) ;
 }
 bzero ( ( char * ) & UNIXaddr , sizeof ( UNIXaddr ) ) ;
 UNIXaddr . sun_family = AF_UNIX ;
 strmov ( UNIXaddr . sun_path , mysqld_unix_port ) ;
 ( void ) unlink ( mysqld_unix_port ) ;
 arg = 1 ;
 ( void ) setsockopt ( unix_sock , SOL_SOCKET , SO_REUSEADDR , ( char * ) & arg , sizeof ( arg ) ) ;
 umask ( 0 ) ;
 if ( bind ( unix_sock , reinterpret_cast < struct sockaddr * > ( & UNIXaddr ) , sizeof ( UNIXaddr ) ) < 0 ) {
 sql_perror ( "Can't start server : Bind on unix socket" ) ;
 sql_print_error ( "Do you already have another mysqld server running on socket: %s ?" , mysqld_unix_port ) ;
 unireg_abort ( 1 ) ;
 }
 umask ( ( ( ~ my_umask ) & 0666 ) ) ;


 }

 DBUG_VOID_RETURN ;
 }
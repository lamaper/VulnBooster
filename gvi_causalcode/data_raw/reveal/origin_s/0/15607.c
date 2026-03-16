static int sql_real_connect ( char * host , char * database , char * user , char * password , uint silent ) {
 if ( connected ) {
 connected = 0 ;
 mysql_close ( & mysql ) ;
 }
 mysql_init ( & mysql ) ;
 if ( opt_init_command ) mysql_options ( & mysql , MYSQL_INIT_COMMAND , opt_init_command ) ;
 if ( opt_connect_timeout ) {
 uint timeout = opt_connect_timeout ;
 mysql_options ( & mysql , MYSQL_OPT_CONNECT_TIMEOUT , ( char * ) & timeout ) ;
 }
 if ( opt_compress ) mysql_options ( & mysql , MYSQL_OPT_COMPRESS , NullS ) ;
 if ( opt_secure_auth ) mysql_options ( & mysql , MYSQL_SECURE_AUTH , ( char * ) & opt_secure_auth ) ;
 if ( using_opt_local_infile ) mysql_options ( & mysql , MYSQL_OPT_LOCAL_INFILE , ( char * ) & opt_local_infile ) ;

 mysql_options ( & mysql , MYSQL_OPT_SSL_VERIFY_SERVER_CERT , ( char * ) & opt_ssl_verify_server_cert ) ;



 char init_command [ 100 ] ;
 sprintf ( init_command , "SET SQL_SAFE_UPDATES=1,SQL_SELECT_LIMIT=%lu,MAX_JOIN_SIZE=%lu" , select_limit , max_join_size ) ;
 mysql_options ( & mysql , MYSQL_INIT_COMMAND , init_command ) ;
 }
 mysql_options ( & mysql , MYSQL_SET_CHARSET_NAME , default_charset ) ;
 if ( opt_plugin_dir && * opt_plugin_dir ) mysql_options ( & mysql , MYSQL_PLUGIN_DIR , opt_plugin_dir ) ;
 if ( opt_default_auth && * opt_default_auth ) mysql_options ( & mysql , MYSQL_DEFAULT_AUTH , opt_default_auth ) ;
 if ( ! mysql_real_connect ( & mysql , host , user , password , database , opt_mysql_port , opt_mysql_unix_port , connect_flag | CLIENT_MULTI_STATEMENTS ) ) {
 if ( ! silent || ( mysql_errno ( & mysql ) != CR_CONN_HOST_ERROR && mysql_errno ( & mysql ) != CR_CONNECTION_ERROR ) ) {
 ( void ) put_error ( & mysql ) ;
 ( void ) fflush ( stdout ) ;
 return ignore_errors ? - 1 : 1 ;
 }
 return - 1 ;
 }
 charset_info = mysql . charset ;
 connected = 1 ;

 if ( mysql . client_flag & CLIENT_PROGRESS ) mysql_options ( & mysql , MYSQL_PROGRESS_CALLBACK , ( void * ) report_progress ) ;



 }
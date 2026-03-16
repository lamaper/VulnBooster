static int connect_to_db ( char * host , char * user , char * passwd ) {
 char buff [ 20 + FN_REFLEN ] ;
 DBUG_ENTER ( "connect_to_db" ) ;
 verbose_msg ( "-- Connecting to %s...\n" , host ? host : "localhost" ) ;
 mysql_init ( & mysql_connection ) ;
 if ( opt_compress ) mysql_options ( & mysql_connection , MYSQL_OPT_COMPRESS , NullS ) ;

 mysql_options ( & mysql_connection , MYSQL_OPT_SSL_VERIFY_SERVER_CERT , ( char * ) & opt_ssl_verify_server_cert ) ;



 if ( opt_plugin_dir && * opt_plugin_dir ) mysql_options ( & mysql_connection , MYSQL_PLUGIN_DIR , opt_plugin_dir ) ;
 if ( opt_default_auth && * opt_default_auth ) mysql_options ( & mysql_connection , MYSQL_DEFAULT_AUTH , opt_default_auth ) ;
 mysql = & mysql_connection ;
 if ( ! mysql_real_connect ( & mysql_connection , host , user , passwd , NULL , opt_mysql_port , opt_mysql_unix_port , 0 ) ) {
 DB_error ( & mysql_connection , "when trying to connect" ) ;
 DBUG_RETURN ( 1 ) ;
 }
 if ( ( mysql_get_server_version ( & mysql_connection ) < 40100 ) || ( opt_compatible_mode & 3 ) ) {
 opt_set_charset = 0 ;
 server_supports_switching_charsets = FALSE ;
 }
 mysql -> reconnect = 0 ;
 my_snprintf ( buff , sizeof ( buff ) , "/*!40100 SET @@SQL_MODE='%s' */" , compatible_mode_normal_str ) ;
 if ( mysql_query_with_error_report ( mysql , 0 , buff ) ) DBUG_RETURN ( 1 ) ;
 if ( opt_tz_utc ) {
 my_snprintf ( buff , sizeof ( buff ) , "/*!40103 SET TIME_ZONE='+00:00' */" ) ;
 if ( mysql_query_with_error_report ( mysql , 0 , buff ) ) DBUG_RETURN ( 1 ) ;
 }
 DBUG_RETURN ( 0 ) ;
 }
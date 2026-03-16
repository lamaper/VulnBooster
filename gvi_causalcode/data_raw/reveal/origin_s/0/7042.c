static void reconnect ( MYSQL * * mysql ) {
 mysql_close ( * mysql ) ;
 * mysql = mysql_client_init ( NULL ) ;
 DIE_UNLESS ( * mysql != 0 ) ;
 * mysql = mysql_real_connect ( * mysql , opt_host , opt_user , opt_password , current_db , opt_port , opt_unix_socket , 0 ) ;
 DIE_UNLESS ( * mysql != 0 ) ;
 }
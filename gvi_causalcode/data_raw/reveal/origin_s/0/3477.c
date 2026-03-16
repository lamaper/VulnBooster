void set_server_version ( void ) {
 char * version_end = server_version + sizeof ( server_version ) - 1 ;
 char * end = strxnmov ( server_version , sizeof ( server_version ) - 1 , MYSQL_SERVER_VERSION , MYSQL_SERVER_SUFFIX_STR , NullS ) ;



 * end = 0 ;
 }
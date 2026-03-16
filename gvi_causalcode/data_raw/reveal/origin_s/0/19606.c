static int reconnect ( void ) {
 if ( opt_reconnect ) {
 put_info ( "No connection. Trying to reconnect..." , INFO_INFO ) ;
 ( void ) com_connect ( ( String * ) 0 , 0 ) ;
 if ( opt_rehash ) com_rehash ( NULL , NULL ) ;
 }
 if ( ! connected ) return put_info ( "Can't connect to the server\n" , INFO_ERROR ) ;
 my_free ( server_version ) ;
 server_version = 0 ;
 return 0 ;
 }
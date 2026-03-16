void config_connections_destroy_all ( void ) {
 while ( config_connections != NULL ) config_connection_destroy ( config_connections ) ;
 }
void config_connection_destroy ( struct config_connection * conn ) {
 DLLIST_REMOVE ( & config_connections , conn ) ;
 io_remove ( & conn -> io ) ;
 i_stream_destroy ( & conn -> input ) ;
 o_stream_destroy ( & conn -> output ) ;
 if ( close ( conn -> fd ) < 0 ) i_error ( "close(config conn) failed: %m" ) ;
 i_free ( conn ) ;
 master_service_client_connection_destroyed ( master_service ) ;
 }
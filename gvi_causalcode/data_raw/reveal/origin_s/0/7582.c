struct config_connection * config_connection_create ( int fd ) {
 struct config_connection * conn ;
 conn = i_new ( struct config_connection , 1 ) ;
 conn -> fd = fd ;
 conn -> input = i_stream_create_fd ( fd , MAX_INBUF_SIZE , FALSE ) ;
 conn -> output = o_stream_create_fd ( fd , ( size_t ) - 1 , FALSE ) ;
 o_stream_set_no_error_handling ( conn -> output , TRUE ) ;
 conn -> io = io_add ( fd , IO_READ , config_connection_input , conn ) ;
 DLLIST_PREPEND ( & config_connections , conn ) ;
 return conn ;
 }
bool handle_new_meta_connection ( int sock ) {
 connection_t * c ;
 sockaddr_t sa ;
 int fd ;
 socklen_t len = sizeof ( sa ) ;
 fd = accept ( sock , & sa . sa , & len ) ;
 if ( fd < 0 ) {
 logger ( LOG_ERR , "Accepting a new connection failed: %s" , sockstrerror ( sockerrno ) ) ;
 return false ;
 }
 sockaddrunmap ( & sa ) ;
 c = new_connection ( ) ;
 c -> name = xstrdup ( "<unknown>" ) ;
 c -> outcipher = myself -> connection -> outcipher ;
 c -> outdigest = myself -> connection -> outdigest ;
 c -> outmaclength = myself -> connection -> outmaclength ;
 c -> outcompression = myself -> connection -> outcompression ;
 c -> address = sa ;
 c -> hostname = sockaddr2hostname ( & sa ) ;
 c -> socket = fd ;
 c -> last_ping_time = now ;
 ifdebug ( CONNECTIONS ) logger ( LOG_NOTICE , "Connection from %s" , c -> hostname ) ;
 configure_tcp ( c ) ;
 connection_add ( c ) ;
 c -> allow_request = ID ;
 send_id ( c ) ;
 return true ;
 }
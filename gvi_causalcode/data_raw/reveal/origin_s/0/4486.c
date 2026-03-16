bool handle_new_meta_connection ( int sock ) {
 static const int max_accept_burst = 10 ;
 static int last_accept_burst ;
 static int last_accept_time ;
 connection_t * c ;
 sockaddr_t sa ;
 int fd ;
 socklen_t len = sizeof ( sa ) ;
 fd = accept ( sock , & sa . sa , & len ) ;
 if ( fd < 0 ) {
 logger ( LOG_ERR , "Accepting a new connection failed: %s" , sockstrerror ( sockerrno ) ) ;
 return false ;
 }
 if ( last_accept_time == now ) {
 last_accept_burst ++ ;
 if ( last_accept_burst >= max_accept_burst ) {
 if ( last_accept_burst == max_accept_burst ) {
 ifdebug ( CONNECTIONS ) logger ( LOG_WARNING , "Throttling incoming connections" ) ;
 }
 tarpit ( fd ) ;
 return false ;
 }
 }
 else {
 last_accept_burst = 0 ;
 last_accept_time = now ;
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
 return true ;
 }
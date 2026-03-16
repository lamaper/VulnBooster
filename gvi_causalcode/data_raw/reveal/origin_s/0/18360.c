void finish_connecting ( connection_t * c ) {
 ifdebug ( CONNECTIONS ) logger ( LOG_INFO , "Connected to %s (%s)" , c -> name , c -> hostname ) ;
 c -> last_ping_time = now ;
 send_id ( c ) ;
 }
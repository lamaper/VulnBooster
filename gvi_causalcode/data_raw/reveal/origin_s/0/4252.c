static void nameserver_write_waiting ( struct nameserver * ns , char waiting ) {
 if ( ns -> write_waiting == waiting ) return ;
 ns -> write_waiting = waiting ;
 ( void ) event_del ( & ns -> event ) ;
 event_set ( & ns -> event , ns -> socket , EV_READ | ( waiting ? EV_WRITE : 0 ) | EV_PERSIST , nameserver_ready_callback , ns ) ;
 if ( event_add ( & ns -> event , NULL ) < 0 ) {
 log ( EVDNS_LOG_WARN , "Error from libevent when adding event for %s" , debug_ntoa ( ns -> address ) ) ;
 }
 }
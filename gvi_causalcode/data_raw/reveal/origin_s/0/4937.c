static void nameserver_probe_failed ( struct nameserver * const ns ) {
 const struct timeval * timeout ;
 ( void ) evtimer_del ( & ns -> timeout_event ) ;
 if ( ns -> state == 1 ) {
 return ;
 }
 timeout = & global_nameserver_timeouts [ MIN ( ns -> failed_times , global_nameserver_timeouts_length - 1 ) ] ;
 ns -> failed_times ++ ;
 if ( evtimer_add ( & ns -> timeout_event , ( struct timeval * ) timeout ) < 0 ) {
 log ( EVDNS_LOG_WARN , "Error from libevent when adding timer event for %s" , debug_ntoa ( ns -> address ) ) ;
 }
 }
static void nameserver_up ( struct nameserver * const ns ) {
 if ( ns -> state ) return ;
 log ( EVDNS_LOG_WARN , "Nameserver %s is back up" , debug_ntoa ( ns -> address ) ) ;
 evtimer_del ( & ns -> timeout_event ) ;
 ns -> state = 1 ;
 ns -> failed_times = 0 ;
 ns -> timedout = 0 ;
 global_good_nameservers ++ ;
 }
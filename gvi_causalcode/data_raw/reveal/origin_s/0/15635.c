int event_haveevents ( struct event_base * base ) {
 return ( base -> event_count > 0 ) ;
 }
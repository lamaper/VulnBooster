int event_base_dispatch ( struct event_base * event_base ) {
 return ( event_base_loop ( event_base , 0 ) ) ;
 }
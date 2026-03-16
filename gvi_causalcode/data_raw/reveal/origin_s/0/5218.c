const char * event_base_get_method ( struct event_base * base ) {
 assert ( base ) ;
 return ( base -> evsel -> name ) ;
 }
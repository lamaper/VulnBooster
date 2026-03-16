void evdns_search_ndots_set ( const int ndots ) {
 if ( ! global_search_state ) global_search_state = search_state_new ( ) ;
 if ( ! global_search_state ) return ;
 global_search_state -> ndots = ndots ;
 }
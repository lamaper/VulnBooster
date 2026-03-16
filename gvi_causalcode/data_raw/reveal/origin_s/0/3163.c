int event_base_set ( struct event_base * base , struct event * ev ) {
 if ( ev -> ev_flags != EVLIST_INIT ) return ( - 1 ) ;
 ev -> ev_base = base ;
 ev -> ev_pri = base -> nactivequeues / 2 ;
 return ( 0 ) ;
 }
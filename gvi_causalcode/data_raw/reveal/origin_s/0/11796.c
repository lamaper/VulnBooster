int event_priority_set ( struct event * ev , int pri ) {
 if ( ev -> ev_flags & EVLIST_ACTIVE ) return ( - 1 ) ;
 if ( pri < 0 || pri >= ev -> ev_base -> nactivequeues ) return ( - 1 ) ;
 ev -> ev_pri = pri ;
 return ( 0 ) ;
 }
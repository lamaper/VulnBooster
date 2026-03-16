void event_active ( struct event * ev , int res , short ncalls ) {
 if ( ev -> ev_flags & EVLIST_ACTIVE ) {
 ev -> ev_res |= res ;
 return ;
 }
 ev -> ev_res = res ;
 ev -> ev_ncalls = ncalls ;
 ev -> ev_pncalls = NULL ;
 event_queue_insert ( ev -> ev_base , ev , EVLIST_ACTIVE ) ;
 }
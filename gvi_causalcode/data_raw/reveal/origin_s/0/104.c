static void timeout_correct ( struct event_base * base , struct timeval * tv ) {
 struct event * * pev ;
 unsigned int size ;
 struct timeval off ;
 if ( use_monotonic ) return ;
 gettime ( base , tv ) ;
 if ( evutil_timercmp ( tv , & base -> event_tv , >= ) ) {
 base -> event_tv = * tv ;
 return ;
 }
 event_debug ( ( "%s: time is running backwards, corrected" , __func__ ) ) ;
 evutil_timersub ( & base -> event_tv , tv , & off ) ;
 pev = base -> timeheap . p ;
 size = base -> timeheap . n ;
 for ( ;
 size -- > 0 ;
 ++ pev ) {
 struct timeval * ev_tv = & ( * * pev ) . ev_timeout ;
 evutil_timersub ( ev_tv , & off , ev_tv ) ;
 }
 base -> event_tv = * tv ;
 }
int event_base_loop ( struct event_base * base , int flags ) {
 const struct eventop * evsel = base -> evsel ;
 void * evbase = base -> evbase ;
 struct timeval tv ;
 struct timeval * tv_p ;
 int res , done ;
 base -> tv_cache . tv_sec = 0 ;
 if ( base -> sig . ev_signal_added ) evsignal_base = base ;
 done = 0 ;
 while ( ! done ) {
 if ( base -> event_gotterm ) {
 base -> event_gotterm = 0 ;
 break ;
 }
 if ( base -> event_break ) {
 base -> event_break = 0 ;
 break ;
 }
 while ( event_gotsig ) {
 event_gotsig = 0 ;
 if ( event_sigcb ) {
 res = ( * event_sigcb ) ( ) ;
 if ( res == - 1 ) {
 errno = EINTR ;
 return ( - 1 ) ;
 }
 }
 }
 timeout_correct ( base , & tv ) ;
 tv_p = & tv ;
 if ( ! base -> event_count_active && ! ( flags & EVLOOP_NONBLOCK ) ) {
 timeout_next ( base , & tv_p ) ;
 }
 else {
 evutil_timerclear ( & tv ) ;
 }
 if ( ! event_haveevents ( base ) ) {
 event_debug ( ( "%s: no events registered." , __func__ ) ) ;
 return ( 1 ) ;
 }
 gettime ( base , & base -> event_tv ) ;
 base -> tv_cache . tv_sec = 0 ;
 res = evsel -> dispatch ( base , evbase , tv_p ) ;
 if ( res == - 1 ) return ( - 1 ) ;
 gettime ( base , & base -> tv_cache ) ;
 timeout_process ( base ) ;
 if ( base -> event_count_active ) {
 event_process_active ( base ) ;
 if ( ! base -> event_count_active && ( flags & EVLOOP_ONCE ) ) done = 1 ;
 }
 else if ( flags & EVLOOP_NONBLOCK ) done = 1 ;
 }
 base -> tv_cache . tv_sec = 0 ;
 event_debug ( ( "%s: asked to terminate loop." , __func__ ) ) ;
 return ( 0 ) ;
 }
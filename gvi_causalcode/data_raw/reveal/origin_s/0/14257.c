static int kq_dispatch ( struct event_base * base , void * arg , struct timeval * tv ) {
 struct kqop * kqop = arg ;
 struct kevent * changes = kqop -> changes ;
 struct kevent * events = kqop -> events ;
 struct event * ev ;
 struct timespec ts , * ts_p = NULL ;
 int i , res ;
 if ( tv != NULL ) {
 TIMEVAL_TO_TIMESPEC ( tv , & ts ) ;
 ts_p = & ts ;
 }
 res = kevent ( kqop -> kq , changes , kqop -> nchanges , events , kqop -> nevents , ts_p ) ;
 kqop -> nchanges = 0 ;
 if ( res == - 1 ) {
 if ( errno != EINTR ) {
 event_warn ( "kevent" ) ;
 return ( - 1 ) ;
 }
 return ( 0 ) ;
 }
 event_debug ( ( "%s: kevent reports %d" , __func__ , res ) ) ;
 for ( i = 0 ;
 i < res ;
 i ++ ) {
 int which = 0 ;
 if ( events [ i ] . flags & EV_ERROR ) {
 if ( events [ i ] . data == EBADF || events [ i ] . data == EINVAL || events [ i ] . data == ENOENT ) continue ;
 errno = events [ i ] . data ;
 return ( - 1 ) ;
 }
 if ( events [ i ] . filter == EVFILT_READ ) {
 which |= EV_READ ;
 }
 else if ( events [ i ] . filter == EVFILT_WRITE ) {
 which |= EV_WRITE ;
 }
 else if ( events [ i ] . filter == EVFILT_SIGNAL ) {
 which |= EV_SIGNAL ;
 }
 if ( ! which ) continue ;
 if ( events [ i ] . filter == EVFILT_SIGNAL ) {
 struct event_list * head = ( struct event_list * ) events [ i ] . udata ;
 TAILQ_FOREACH ( ev , head , ev_signal_next ) {
 event_active ( ev , which , events [ i ] . data ) ;
 }
 }
 else {
 ev = ( struct event * ) events [ i ] . udata ;
 if ( ! ( ev -> ev_events & EV_PERSIST ) ) ev -> ev_flags &= ~ EVLIST_X_KQINKERNEL ;
 event_active ( ev , which , 1 ) ;
 }
 }
 return ( 0 ) ;
 }
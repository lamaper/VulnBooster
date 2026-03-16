int event_base_once ( struct event_base * base , int fd , short events , void ( * callback ) ( int , short , void * ) , void * arg , const struct timeval * tv ) {
 struct event_once * eonce ;
 struct timeval etv ;
 int res ;
 if ( events & EV_SIGNAL ) return ( - 1 ) ;
 if ( ( eonce = calloc ( 1 , sizeof ( struct event_once ) ) ) == NULL ) return ( - 1 ) ;
 eonce -> cb = callback ;
 eonce -> arg = arg ;
 if ( events == EV_TIMEOUT ) {
 if ( tv == NULL ) {
 evutil_timerclear ( & etv ) ;
 tv = & etv ;
 }
 evtimer_set ( & eonce -> ev , event_once_cb , eonce ) ;
 }
 else if ( events & ( EV_READ | EV_WRITE ) ) {
 events &= EV_READ | EV_WRITE ;
 event_set ( & eonce -> ev , fd , events , event_once_cb , eonce ) ;
 }
 else {
 free ( eonce ) ;
 return ( - 1 ) ;
 }
 res = event_base_set ( base , & eonce -> ev ) ;
 if ( res == 0 ) res = event_add ( & eonce -> ev , tv ) ;
 if ( res != 0 ) {
 free ( eonce ) ;
 return ( res ) ;
 }
 return ( 0 ) ;
 }
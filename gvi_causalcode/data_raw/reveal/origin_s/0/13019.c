int evsignal_add ( struct event * ev ) {
 int evsignal ;
 struct event_base * base = ev -> ev_base ;
 struct evsignal_info * sig = & ev -> ev_base -> sig ;
 if ( ev -> ev_events & ( EV_READ | EV_WRITE ) ) event_errx ( 1 , "%s: EV_SIGNAL incompatible use" , __func__ ) ;
 evsignal = EVENT_SIGNAL ( ev ) ;
 assert ( evsignal >= 0 && evsignal < NSIG ) ;
 if ( TAILQ_EMPTY ( & sig -> evsigevents [ evsignal ] ) ) {
 event_debug ( ( "%s: %p: changing signal handler" , __func__ , ev ) ) ;
 if ( _evsignal_set_handler ( base , evsignal , evsignal_handler ) == - 1 ) return ( - 1 ) ;
 evsignal_base = base ;
 if ( ! sig -> ev_signal_added ) {
 if ( event_add ( & sig -> ev_signal , NULL ) ) return ( - 1 ) ;
 sig -> ev_signal_added = 1 ;
 }
 }
 TAILQ_INSERT_TAIL ( & sig -> evsigevents [ evsignal ] , ev , ev_signal_next ) ;
 return ( 0 ) ;
 }
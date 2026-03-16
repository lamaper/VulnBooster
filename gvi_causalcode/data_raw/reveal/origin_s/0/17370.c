int evsignal_del ( struct event * ev ) {
 struct event_base * base = ev -> ev_base ;
 struct evsignal_info * sig = & base -> sig ;
 int evsignal = EVENT_SIGNAL ( ev ) ;
 assert ( evsignal >= 0 && evsignal < NSIG ) ;
 TAILQ_REMOVE ( & sig -> evsigevents [ evsignal ] , ev , ev_signal_next ) ;
 if ( ! TAILQ_EMPTY ( & sig -> evsigevents [ evsignal ] ) ) return ( 0 ) ;
 event_debug ( ( "%s: %p: restoring signal handler" , __func__ , ev ) ) ;
 return ( _evsignal_restore_handler ( ev -> ev_base , EVENT_SIGNAL ( ev ) ) ) ;
 }
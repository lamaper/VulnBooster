void evsignal_process ( struct event_base * base ) {
 struct evsignal_info * sig = & base -> sig ;
 struct event * ev , * next_ev ;
 sig_atomic_t ncalls ;
 int i ;
 base -> sig . evsignal_caught = 0 ;
 for ( i = 1 ;
 i < NSIG ;
 ++ i ) {
 ncalls = sig -> evsigcaught [ i ] ;
 if ( ncalls == 0 ) continue ;
 sig -> evsigcaught [ i ] -= ncalls ;
 for ( ev = TAILQ_FIRST ( & sig -> evsigevents [ i ] ) ;
 ev != NULL ;
 ev = next_ev ) {
 next_ev = TAILQ_NEXT ( ev , ev_signal_next ) ;
 if ( ! ( ev -> ev_events & EV_PERSIST ) ) event_del ( ev ) ;
 event_active ( ev , EV_SIGNAL , ncalls ) ;
 }
 }
 }
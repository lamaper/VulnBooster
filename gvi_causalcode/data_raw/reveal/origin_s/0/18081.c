static int kq_del ( void * arg , struct event * ev ) {
 struct kqop * kqop = arg ;
 struct kevent kev ;
 if ( ! ( ev -> ev_flags & EVLIST_X_KQINKERNEL ) ) return ( 0 ) ;
 if ( ev -> ev_events & EV_SIGNAL ) {
 int nsignal = EVENT_SIGNAL ( ev ) ;
 struct timespec timeout = {
 0 , 0 }
 ;
 assert ( nsignal >= 0 && nsignal < NSIG ) ;
 TAILQ_REMOVE ( & kqop -> evsigevents [ nsignal ] , ev , ev_signal_next ) ;
 if ( TAILQ_EMPTY ( & kqop -> evsigevents [ nsignal ] ) ) {
 memset ( & kev , 0 , sizeof ( kev ) ) ;
 kev . ident = nsignal ;
 kev . filter = EVFILT_SIGNAL ;
 kev . flags = EV_DELETE ;
 if ( kevent ( kqop -> kq , & kev , 1 , NULL , 0 , & timeout ) == - 1 ) return ( - 1 ) ;
 if ( _evsignal_restore_handler ( ev -> ev_base , nsignal ) == - 1 ) return ( - 1 ) ;
 }
 ev -> ev_flags &= ~ EVLIST_X_KQINKERNEL ;
 return ( 0 ) ;
 }
 if ( ev -> ev_events & EV_READ ) {
 memset ( & kev , 0 , sizeof ( kev ) ) ;
 kev . ident = ev -> ev_fd ;
 kev . filter = EVFILT_READ ;
 kev . flags = EV_DELETE ;
 if ( kq_insert ( kqop , & kev ) == - 1 ) return ( - 1 ) ;
 ev -> ev_flags &= ~ EVLIST_X_KQINKERNEL ;
 }
 if ( ev -> ev_events & EV_WRITE ) {
 memset ( & kev , 0 , sizeof ( kev ) ) ;
 kev . ident = ev -> ev_fd ;
 kev . filter = EVFILT_WRITE ;
 kev . flags = EV_DELETE ;
 if ( kq_insert ( kqop , & kev ) == - 1 ) return ( - 1 ) ;
 ev -> ev_flags &= ~ EVLIST_X_KQINKERNEL ;
 }
 return ( 0 ) ;
 }
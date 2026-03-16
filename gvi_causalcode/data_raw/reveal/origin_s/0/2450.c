static int kq_add ( void * arg , struct event * ev ) {
 struct kqop * kqop = arg ;
 struct kevent kev ;
 if ( ev -> ev_events & EV_SIGNAL ) {
 int nsignal = EVENT_SIGNAL ( ev ) ;
 assert ( nsignal >= 0 && nsignal < NSIG ) ;
 if ( TAILQ_EMPTY ( & kqop -> evsigevents [ nsignal ] ) ) {
 struct timespec timeout = {
 0 , 0 }
 ;
 memset ( & kev , 0 , sizeof ( kev ) ) ;
 kev . ident = nsignal ;
 kev . filter = EVFILT_SIGNAL ;
 kev . flags = EV_ADD ;
 kev . udata = PTR_TO_UDATA ( & kqop -> evsigevents [ nsignal ] ) ;
 if ( kevent ( kqop -> kq , & kev , 1 , NULL , 0 , & timeout ) == - 1 ) return ( - 1 ) ;
 if ( _evsignal_set_handler ( ev -> ev_base , nsignal , kq_sighandler ) == - 1 ) return ( - 1 ) ;
 }
 TAILQ_INSERT_TAIL ( & kqop -> evsigevents [ nsignal ] , ev , ev_signal_next ) ;
 ev -> ev_flags |= EVLIST_X_KQINKERNEL ;
 return ( 0 ) ;
 }
 if ( ev -> ev_events & EV_READ ) {
 memset ( & kev , 0 , sizeof ( kev ) ) ;
 kev . ident = ev -> ev_fd ;
 kev . filter = EVFILT_READ ;


 if ( ! ( ev -> ev_events & EV_PERSIST ) ) kev . flags |= EV_ONESHOT ;
 kev . udata = PTR_TO_UDATA ( ev ) ;
 if ( kq_insert ( kqop , & kev ) == - 1 ) return ( - 1 ) ;
 ev -> ev_flags |= EVLIST_X_KQINKERNEL ;
 }
 if ( ev -> ev_events & EV_WRITE ) {
 memset ( & kev , 0 , sizeof ( kev ) ) ;
 kev . ident = ev -> ev_fd ;
 kev . filter = EVFILT_WRITE ;
 kev . flags = EV_ADD ;
 if ( ! ( ev -> ev_events & EV_PERSIST ) ) kev . flags |= EV_ONESHOT ;
 kev . udata = PTR_TO_UDATA ( ev ) ;
 if ( kq_insert ( kqop , & kev ) == - 1 ) return ( - 1 ) ;
 ev -> ev_flags |= EVLIST_X_KQINKERNEL ;
 }
 return ( 0 ) ;
 }
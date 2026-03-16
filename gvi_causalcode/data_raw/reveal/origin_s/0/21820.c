static int kq_insert ( struct kqop * kqop , struct kevent * kev ) {
 int nevents = kqop -> nevents ;
 if ( kqop -> nchanges == nevents ) {
 struct kevent * newchange ;
 struct kevent * newresult ;
 nevents *= 2 ;
 newchange = realloc ( kqop -> changes , nevents * sizeof ( struct kevent ) ) ;
 if ( newchange == NULL ) {
 event_warn ( "%s: malloc" , __func__ ) ;
 return ( - 1 ) ;
 }
 kqop -> changes = newchange ;
 newresult = realloc ( kqop -> events , nevents * sizeof ( struct kevent ) ) ;
 if ( newresult == NULL ) {
 event_warn ( "%s: malloc" , __func__ ) ;
 return ( - 1 ) ;
 }
 kqop -> events = newresult ;
 kqop -> nevents = nevents ;
 }
 memcpy ( & kqop -> changes [ kqop -> nchanges ++ ] , kev , sizeof ( struct kevent ) ) ;
 event_debug ( ( "%s: fd %d %s%s" , __func__ , ( int ) kev -> ident , kev -> filter == EVFILT_READ ? "EVFILT_READ" : "EVFILT_WRITE" , kev -> flags == EV_DELETE ? " (del)" : "" ) ) ;
 return ( 0 ) ;
 }
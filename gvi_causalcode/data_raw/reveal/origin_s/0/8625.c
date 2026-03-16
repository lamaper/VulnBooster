static void event_loopexit_cb ( int fd , short what , void * arg ) {
 struct event_base * base = arg ;
 base -> event_gotterm = 1 ;
 }
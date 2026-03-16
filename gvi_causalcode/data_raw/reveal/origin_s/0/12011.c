static void signal_cb ( int fd , short event , void * arg ) {
 struct event * signal = arg ;
 printf ( "%s: got signal %d\n" , __func__ , EVENT_SIGNAL ( signal ) ) ;
 if ( called >= 2 ) event_del ( signal ) ;
 called ++ ;
 }
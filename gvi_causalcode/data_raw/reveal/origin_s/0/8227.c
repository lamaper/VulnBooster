static void timeout_cb_swp ( int fd , short event , void * arg ) {
 if ( called == - 1 ) {
 struct timeval tv = {
 5 , 0 }
 ;
 called = 0 ;
 evtimer_add ( ( struct event * ) arg , & tv ) ;
 raise ( SIGUSR1 ) ;
 return ;
 }
 test_ok = 0 ;
 event_loopexit ( NULL ) ;
 }
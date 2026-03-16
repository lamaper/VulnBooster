static void child_signal_cb ( int fd , short event , void * arg ) {
 struct timeval tv ;
 int * pint = arg ;
 * pint = 1 ;
 tv . tv_usec = 500000 ;
 tv . tv_sec = 0 ;
 event_loopexit ( & tv ) ;
 }
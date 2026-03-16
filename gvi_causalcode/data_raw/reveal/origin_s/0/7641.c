static void signal_cb ( int fd , short event , void * arg ) {
 struct event * ev = arg ;
 signal_del ( ev ) ;
 test_ok = 1 ;
 }
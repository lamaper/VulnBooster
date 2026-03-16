static void break_cb ( int fd , short events , void * arg ) {
 test_ok = 1 ;
 event_loopbreak ( ) ;
 }
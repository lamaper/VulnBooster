static void test_multiple_cb ( int fd , short event , void * arg ) {
 if ( event & EV_READ ) test_ok |= 1 ;
 else if ( event & EV_WRITE ) test_ok |= 2 ;
 }
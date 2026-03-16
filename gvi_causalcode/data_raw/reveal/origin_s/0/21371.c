static void test_priorities_cb ( int fd , short what , void * arg ) {
 struct test_pri_event * pri = arg ;
 struct timeval tv ;
 if ( pri -> count == 3 ) {
 event_loopexit ( NULL ) ;
 return ;
 }
 pri -> count ++ ;
 evutil_timerclear ( & tv ) ;
 event_add ( & pri -> ev , & tv ) ;
 }
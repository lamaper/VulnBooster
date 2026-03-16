static void test_loopexit ( void ) {
 struct timeval tv , tv_start , tv_end ;
 struct event ev ;
 setup_test ( "Loop exit: " ) ;
 tv . tv_usec = 0 ;
 tv . tv_sec = 60 * 60 * 24 ;
 evtimer_set ( & ev , timeout_cb , NULL ) ;
 evtimer_add ( & ev , & tv ) ;
 tv . tv_usec = 0 ;
 tv . tv_sec = 1 ;
 event_loopexit ( & tv ) ;
 evutil_gettimeofday ( & tv_start , NULL ) ;
 event_dispatch ( ) ;
 evutil_gettimeofday ( & tv_end , NULL ) ;
 evutil_timersub ( & tv_end , & tv_start , & tv_end ) ;
 evtimer_del ( & ev ) ;
 if ( tv . tv_sec < 2 ) test_ok = 1 ;
 cleanup_test ( ) ;
 }
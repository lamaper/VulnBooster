static void timeout_cb ( int fd , short event , void * arg ) {
 struct timeval tv ;
 int diff ;
 evutil_gettimeofday ( & tcalled , NULL ) ;
 if ( evutil_timercmp ( & tcalled , & tset , > ) ) evutil_timersub ( & tcalled , & tset , & tv ) ;
 else evutil_timersub ( & tset , & tcalled , & tv ) ;
 diff = tv . tv_sec * 1000 + tv . tv_usec / 1000 - SECONDS * 1000 ;
 if ( diff < 0 ) diff = - diff ;
 if ( diff < 100 ) test_ok = 1 ;
 }
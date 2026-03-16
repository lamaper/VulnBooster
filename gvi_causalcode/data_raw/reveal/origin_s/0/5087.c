static void http_badreq_successcb ( int fd , short what , void * arg ) {
 event_debug ( ( "%s: called (what=%04x, arg=%p)" , __func__ , what , arg ) ) ;
 event_loopexit ( NULL ) ;
 }
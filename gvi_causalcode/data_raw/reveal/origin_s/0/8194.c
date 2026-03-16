static void http_badreq_errorcb ( struct bufferevent * bev , short what , void * arg ) {
 event_debug ( ( "%s: called (what=%04x, arg=%p)" , __func__ , what , arg ) ) ;
 }
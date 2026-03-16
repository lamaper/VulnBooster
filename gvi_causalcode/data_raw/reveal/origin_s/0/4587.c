static void evhttp_connection_start_detectclose ( struct evhttp_connection * evcon ) {
 evcon -> flags |= EVHTTP_CON_CLOSEDETECT ;
 if ( event_initialized ( & evcon -> close_ev ) ) event_del ( & evcon -> close_ev ) ;
 event_set ( & evcon -> close_ev , evcon -> fd , EV_READ , evhttp_detect_close_cb , evcon ) ;
 EVHTTP_BASE_SET ( evcon , & evcon -> close_ev ) ;
 event_add ( & evcon -> close_ev , NULL ) ;
 }
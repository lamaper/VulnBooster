void evhttp_start_read ( struct evhttp_connection * evcon ) {
 if ( event_initialized ( & evcon -> ev ) ) event_del ( & evcon -> ev ) ;
 event_set ( & evcon -> ev , evcon -> fd , EV_READ , evhttp_read , evcon ) ;
 EVHTTP_BASE_SET ( evcon , & evcon -> ev ) ;
 evhttp_add_event ( & evcon -> ev , evcon -> timeout , HTTP_READ_TIMEOUT ) ;
 evcon -> state = EVCON_READING_FIRSTLINE ;
 }
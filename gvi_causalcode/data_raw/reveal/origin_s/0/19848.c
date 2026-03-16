void evhttp_write_buffer ( struct evhttp_connection * evcon , void ( * cb ) ( struct evhttp_connection * , void * ) , void * arg ) {
 event_debug ( ( "%s: preparing to write buffer\n" , __func__ ) ) ;
 evcon -> cb = cb ;
 evcon -> cb_arg = arg ;
 if ( event_pending ( & evcon -> ev , EV_WRITE | EV_TIMEOUT , NULL ) ) event_del ( & evcon -> ev ) ;
 event_set ( & evcon -> ev , evcon -> fd , EV_WRITE , evhttp_write , evcon ) ;
 EVHTTP_BASE_SET ( evcon , & evcon -> ev ) ;
 evhttp_add_event ( & evcon -> ev , evcon -> timeout , HTTP_WRITE_TIMEOUT ) ;
 }
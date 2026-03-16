static void evhttp_connectioncb ( int fd , short what , void * arg ) {
 struct evhttp_connection * evcon = arg ;
 int error ;
 socklen_t errsz = sizeof ( error ) ;
 if ( what == EV_TIMEOUT ) {
 event_debug ( ( "%s: connection timeout for \"%s:%d\" on %d" , __func__ , evcon -> address , evcon -> port , evcon -> fd ) ) ;
 goto cleanup ;
 }
 if ( getsockopt ( evcon -> fd , SOL_SOCKET , SO_ERROR , ( void * ) & error , & errsz ) == - 1 ) {
 event_debug ( ( "%s: getsockopt for \"%s:%d\" on %d" , __func__ , evcon -> address , evcon -> port , evcon -> fd ) ) ;
 goto cleanup ;
 }
 if ( error ) {
 event_debug ( ( "%s: connect failed for \"%s:%d\" on %d: %s" , __func__ , evcon -> address , evcon -> port , evcon -> fd , strerror ( error ) ) ) ;
 goto cleanup ;
 }
 event_debug ( ( "%s: connected to \"%s:%d\" on %d\n" , __func__ , evcon -> address , evcon -> port , evcon -> fd ) ) ;
 evcon -> retry_cnt = 0 ;
 evcon -> state = EVCON_IDLE ;
 evhttp_request_dispatch ( evcon ) ;
 return ;
 cleanup : if ( evcon -> retry_max < 0 || evcon -> retry_cnt < evcon -> retry_max ) {
 evtimer_set ( & evcon -> ev , evhttp_connection_retry , evcon ) ;
 EVHTTP_BASE_SET ( evcon , & evcon -> ev ) ;
 evhttp_add_event ( & evcon -> ev , MIN ( 3600 , 2 << evcon -> retry_cnt ) , HTTP_CONNECT_TIMEOUT ) ;
 evcon -> retry_cnt ++ ;
 return ;
 }
 evhttp_connection_reset ( evcon ) ;
 while ( TAILQ_FIRST ( & evcon -> requests ) != NULL ) {
 struct evhttp_request * request = TAILQ_FIRST ( & evcon -> requests ) ;
 TAILQ_REMOVE ( & evcon -> requests , request , next ) ;
 request -> evcon = NULL ;
 request -> cb ( request , request -> cb_arg ) ;
 evhttp_request_free ( request ) ;
 }
 }
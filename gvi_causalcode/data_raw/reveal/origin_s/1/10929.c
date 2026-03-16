void evhttp_connection_fail ( struct evhttp_connection * evcon , enum evhttp_connection_error error ) {
 struct evhttp_request * req = TAILQ_FIRST ( & evcon -> requests ) ;
 void ( * cb ) ( struct evhttp_request * , void * ) ;
 void * cb_arg ;
 assert ( req != NULL ) ;
 if ( evcon -> flags & EVHTTP_CON_INCOMING ) {
 if ( evhttp_connection_incoming_fail ( req , error ) == - 1 ) evhttp_connection_free ( evcon ) ;
 return ;
 }
 cb = req -> cb ;
 cb_arg = req -> cb_arg ;
 TAILQ_REMOVE ( & evcon -> requests , req , next ) ;
 evhttp_request_free ( req ) ;
 evhttp_connection_reset ( evcon ) ;
 if ( TAILQ_FIRST ( & evcon -> requests ) != NULL ) evhttp_connection_connect ( evcon ) ;
 if ( cb != NULL ) ( * cb ) ( NULL , cb_arg ) ;
 }
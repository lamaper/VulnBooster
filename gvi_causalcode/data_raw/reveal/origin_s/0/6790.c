static int evhttp_associate_new_request_with_connection ( struct evhttp_connection * evcon ) {
 struct evhttp * http = evcon -> http_server ;
 struct evhttp_request * req ;
 if ( ( req = evhttp_request_new ( evhttp_handle_request , http ) ) == NULL ) return ( - 1 ) ;
 req -> evcon = evcon ;
 req -> flags |= EVHTTP_REQ_OWN_CONNECTION ;
 TAILQ_INSERT_TAIL ( & evcon -> requests , req , next ) ;
 req -> kind = EVHTTP_REQUEST ;
 if ( ( req -> remote_host = strdup ( evcon -> address ) ) == NULL ) event_err ( 1 , "%s: strdup" , __func__ ) ;
 req -> remote_port = evcon -> port ;
 evhttp_start_read ( evcon ) ;
 return ( 0 ) ;
 }
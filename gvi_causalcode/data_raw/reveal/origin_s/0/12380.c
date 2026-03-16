struct evdns_server_port * evdns_add_server_port ( int socket , int is_tcp , evdns_request_callback_fn_type cb , void * user_data ) {
 struct evdns_server_port * port ;
 if ( ! ( port = malloc ( sizeof ( struct evdns_server_port ) ) ) ) return NULL ;
 memset ( port , 0 , sizeof ( struct evdns_server_port ) ) ;
 assert ( ! is_tcp ) ;
 port -> socket = socket ;
 port -> refcnt = 1 ;
 port -> choked = 0 ;
 port -> closing = 0 ;
 port -> user_callback = cb ;
 port -> user_data = user_data ;
 port -> pending_replies = NULL ;
 event_set ( & port -> event , port -> socket , EV_READ | EV_PERSIST , server_port_ready_callback , port ) ;
 event_add ( & port -> event , NULL ) ;
 return port ;
 }
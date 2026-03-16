int evdns_server_request_drop ( struct evdns_server_request * _req ) {
 struct server_request * req = TO_SERVER_REQUEST ( _req ) ;
 server_request_free ( req ) ;
 return 0 ;
 }
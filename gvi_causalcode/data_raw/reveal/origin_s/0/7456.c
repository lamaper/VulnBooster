bool send_id ( connection_t * c ) {
 if ( proxytype && c -> outgoing && ! c -> status . proxy_passed ) {
 return send_proxyrequest ( c ) ;
 }
 return send_request ( c , "%d %s %d" , ID , myself -> connection -> name , myself -> connection -> protocol_version ) ;
 }
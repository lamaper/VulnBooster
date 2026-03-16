int evdns_server_request_get_requesting_addr ( struct evdns_server_request * _req , struct sockaddr * sa , int addr_len ) {
 struct server_request * req = TO_SERVER_REQUEST ( _req ) ;
 if ( addr_len < ( int ) req -> addrlen ) return - 1 ;
 memcpy ( sa , & ( req -> addr ) , req -> addrlen ) ;
 return req -> addrlen ;
 }
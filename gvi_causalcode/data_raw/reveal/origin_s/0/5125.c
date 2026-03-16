bool send_req_key ( node_t * to ) {
 return send_request ( to -> nexthop -> connection , "%d %s %s" , REQ_KEY , myself -> name , to -> name ) ;
 }
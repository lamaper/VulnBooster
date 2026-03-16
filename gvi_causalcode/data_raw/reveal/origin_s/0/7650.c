bool send_del_edge ( connection_t * c , const edge_t * e ) {
 return send_request ( c , "%d %x %s %s" , DEL_EDGE , rand ( ) , e -> from -> name , e -> to -> name ) ;
 }
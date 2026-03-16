bool send_add_edge ( connection_t * c , const edge_t * e ) {
 bool x ;
 char * address , * port ;
 sockaddr2str ( & e -> address , & address , & port ) ;
 x = send_request ( c , "%d %x %s %s %s %s %x %d" , ADD_EDGE , rand ( ) , e -> from -> name , e -> to -> name , address , port , e -> options , e -> weight ) ;
 free ( address ) ;
 free ( port ) ;
 return x ;
 }
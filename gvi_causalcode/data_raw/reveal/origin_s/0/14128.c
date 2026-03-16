void send_key_changed ( void ) {
 avl_node_t * node ;
 connection_t * c ;
 send_request ( everyone , "%d %x %s" , KEY_CHANGED , rand ( ) , myself -> name ) ;
 for ( node = connection_tree -> head ;
 node ;
 node = node -> next ) {
 c = node -> data ;
 if ( c -> status . active && c -> node && c -> node -> status . reachable ) {
 send_ans_key ( c -> node ) ;
 }
 }
 }
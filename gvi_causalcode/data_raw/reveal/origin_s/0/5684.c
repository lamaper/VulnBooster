static void send_everything ( connection_t * c ) {
 avl_node_t * node , * node2 ;
 node_t * n ;
 subnet_t * s ;
 edge_t * e ;
 if ( tunnelserver ) {
 for ( node = myself -> subnet_tree -> head ;
 node ;
 node = node -> next ) {
 s = node -> data ;
 send_add_subnet ( c , s ) ;
 }
 return ;
 }
 for ( node = node_tree -> head ;
 node ;
 node = node -> next ) {
 n = node -> data ;
 for ( node2 = n -> subnet_tree -> head ;
 node2 ;
 node2 = node2 -> next ) {
 s = node2 -> data ;
 send_add_subnet ( c , s ) ;
 }
 for ( node2 = n -> edge_tree -> head ;
 node2 ;
 node2 = node2 -> next ) {
 e = node2 -> data ;
 send_add_edge ( c , e ) ;
 }
 }
 }